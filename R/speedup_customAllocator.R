if (!requireNamespace("pacman", quietly = TRUE)) install.packages("pacman", repos = "http://cran.us.r-project.org")
pacman::p_load(ggplot2, tidyverse)

# Set theme
theme_set(theme_bw())

# Load helper functions
source("utils.R")

json_dir_custom_allocator <- "json_data/speedup_customAllocator/ca"
data_custom <- from_json_dir_data(json_dir_custom_allocator)

json_dir_default_allocator <- "json_data/speedup_customAllocator/da"
data_default <- from_json_dir_data(json_dir_default_allocator)

plot_title <- NULL

# Load and preprocess data
data <- bind_rows(
  data_default %>% mutate(allocator = "default"),
  data_custom %>% mutate(allocator = "custom")
) %>%
  mutate(elements = get_elements(name), ) %>%
  filter(elements == 2^29) %>% # Filter for a specific problem size
  mutate(algorithm = get_algorithm(name, kernel_its)) %>%
  mutate(name = get_name(name)) %>%
  select(name, elements, real_time, algorithm, allocator) %>%
  sort_data_seq_first()

# Process speedup data
speedup_data <- data %>%
  complete(algorithm, name, fill = list(real_time = NA)) %>% # Add missing combinations with NA
  spread(key = allocator, value = real_time, fill = NA) %>% # Reshape data to have separate columns for default and custom
  mutate(
    speedup = ifelse(is.na(default) | is.na(custom), NA, default / custom),
    algorithm = factor(algorithm, levels = unique(algorithm)),
  ) %>%
  mutate(
    speedup_label = ifelse(is.na(speedup), "N/A", sprintf("%.2f", speedup)), # Create a label for speedup
    speedup = ifelse(is.na(speedup), 0, speedup) # Replace NA with 0 for plotting
  )

palette <- get_palette(speedup_data$name, skip = 2)

# Create a bar plot for the aggregated speedup
p <- ggplot(
  speedup_data,
  aes(x = algorithm, y = speedup, fill = name)
) +
  geom_bar(stat = "identity", position = "dodge", color = "black") + # Create grouped bars for each name
  geom_hline(yintercept = 1.0, linetype = "dashed", color = "black", linewidth = 1) + # Add a horizontal line at y = 1.0
  geom_text(
    aes(label = speedup_label),
    position = position_dodge(width = 0.9), # Position text to match the bars
    vjust = 0.4, # Center the text on the bar
    hjust = -0.2, # Place text above the bars
    angle = 90, # Rotate the text vertically
    size = 4.8,
  ) +
  scale_y_continuous(
    breaks = seq(0, max(speedup_data$speedup, na.rm = TRUE) + 0.2, by = 0.2), # Extend y-axis to accommodate text
    limits = c(0, max(speedup_data$speedup, na.rm = TRUE) + 0.2), # Extend the y-axis to ensure text is visible
    labels = scales::comma
  ) +
  scale_fill_manual(
    name = NULL,
    values = palette,
  ) +
  guides(fill = guide_legend(ncol = 3)) + # Arrange legend in 3 columns
  labs(
    title = plot_title,
    y = "Speedup (vs default allocator)",
    x = "Algorithm"
  ) +
  theme(
    panel.grid.minor = element_blank(),
    panel.grid.major = element_line(color = "grey", linewidth = 0.25, linetype = "dashed"),
    panel.border = element_rect(color = "black", fill = NA, linewidth = 0.5),
    plot.title = element_text(hjust = 0.5, size = 25, face = "bold"),
    axis.line = element_blank(),
    axis.ticks = element_line(color = "black"),
    axis.ticks.length = unit(-0.25, "cm"),
    axis.title = element_text(size = 26),
    axis.text = element_text(size = 11, colour = "black"),
    axis.text.x = element_text(size = 12.3),
    axis.text.y = element_text(size = 14),
    legend.text = element_text(size = 18),
    legend.key.width = unit(0.5, "cm"), # helps prevent label crowding
    legend.key.height = unit(0.4, "cm"), # keep key boxes compact
    legend.margin = margin(5, 5, 5, 5),
    legend.position = "top",
    legend.box = "horizontal",
    legend.background = element_rect(
      color = "black",
      linewidth = 0.5
    )
  )

plot_width <- 8
plot_height <- 6

show_plot_with_size(p, width = plot_width, height = plot_height)

filename <- "speedup_customAllocator.pdf"
save_to_cairo_pdf(p, filename, width = plot_width, height = plot_height)

# Save the plot to a PDF file and close the window if open
dev.off()
rm(list = ls()) # Clean up the environment
