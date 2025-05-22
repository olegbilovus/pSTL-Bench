install.packages("pacman", repos = "http://cran.us.r-project.org")
library(pacman)
pacman::p_load(rio, ggplot2, tidyverse)
theme_set(theme_bw())

source("utils.R")

json_dir_custom_allocator <- "json_data/speedup_customAllocator/ca"
data_custom <- from_json_dir_data(json_dir_custom_allocator)

json_dir_default_allocator <- "json_data/speedup_customAllocator/da"
data_default <- from_json_dir_data(json_dir_default_allocator)

plot_title <- NULL

# Combine the data
data <- bind_rows(
  data_default %>% mutate(allocator = "default"),
  data_custom %>% mutate(allocator = "custom")
)

# Extract the number of elements from the 'name' column
data <- data %>%
  mutate(
    elements = get_elements(name),
  )

# Filter only the rows with 2^30 elements
data <- data %>%
  filter(elements == 2^30)

# extract the algorithm name from the 'name' column
data <- data %>%
  mutate(
    algorithm = get_algorithm(name, kernel_its),
  )

# Extract the name for the plot
data <- data %>%
  mutate(
    name = get_name(name),
  )

data <- data %>%
  select(name, elements, real_time, algorithm, allocator)

# Order the data by name
data <- data %>%
  mutate(name = factor(name, levels = unique(name)))

# Ensure all combinations of algorithm and name are present, filling missing values with NA
speedup_data <- data %>%
  complete(algorithm, name, fill = list(real_time = NA)) %>% # Add missing combinations with NA
  spread(key = allocator, value = real_time, fill = NA) %>% # Reshape data to have separate columns for default and custom
  mutate(
    speedup = ifelse(is.na(default) | is.na(custom), NA, default / custom),
    algorithm = factor(algorithm, levels = unique(algorithm)), # Ensure the algorithm column is a factor
  )

# Calculate speedup, set NA if data is missing
speedup_data <- speedup_data %>%
  mutate(
    speedup_label = ifelse(is.na(speedup), "N/A", sprintf("%.2f", speedup)), # Create a label for speedup
    speedup = ifelse(is.na(speedup), 0, speedup) # Replace NA with 0 for plotting
  )

# Create a bar plot for the aggregated speedup
p <- ggplot(speedup_data, aes(x = algorithm, y = speedup, fill = name)) +
  geom_bar(stat = "identity", position = "dodge", color = "black") + # Create grouped bars for each name
  geom_hline(yintercept = 1.0, linetype = "dashed", color = "black", linewidth = 0.7) + # Add a horizontal line at y = 1.0
  geom_text(
    aes(label = speedup_label),
    position = position_dodge(width = 0.9), # Position text to match the bars
    vjust = 0, # Center the text on the bar
    hjust = -0.2, # Place text above the bars
    angle = 90, # Rotate the text vertically
    size = 3,
  ) +
  scale_y_continuous(
    breaks = seq(0, max(speedup_data$speedup, na.rm = TRUE) + 0.2, by = 0.2), # Extend y-axis to accommodate text
    limits = c(0, max(speedup_data$speedup, na.rm = TRUE) + 0.2), # Extend the y-axis to ensure text is visible
    name = "Speedup (vs default allocator)",
    labels = scales::comma
  ) +
  scale_x_discrete(name = "Algorithm") +
  scale_fill_manual(
    name = NULL,
    values = scales::hue_pal()(length(unique(speedup_data$name))) # Assign distinct colors to names
  ) +
  labs(title = plot_title) +
  theme(
    panel.grid.minor = element_blank(),
    panel.grid.major = element_line(color = "grey", linewidth = 0.25, linetype = "dashed"),
    legend.position = "top", # Move the legend to the top of the chart
    legend.box = "horizontal", # Arrange legend items horizontally
    legend.background = element_rect(fill = "white", color = scales::alpha("black", 0.5)), # Add a border around the legend
    legend.margin = margin(5, 5, 5, 5), # Add some padding inside the legend box
    panel.border = element_rect(color = "black", fill = NA, linewidth = 0.5), # Add a border around the plot
    plot.title = element_text(hjust = 0.5) # Center the title
  )

p


# interactive plot
# pacman::p_load(plotly)
# ggplotly(p)