# Load required packages
install.packages("pacman", repos = "http://cran.us.r-project.org")
library(pacman)
p_load(rio, ggplot2, tidyverse, lemon)

# Set theme
theme_set(theme_bw())

# Load helper functions
source("utils.R")

# Define paths and constants
json_dir <- "json_data/speedup_threads/sort/"
plot_title <- NULL
SEQ_NAME <- get_seq_name()

# Load and preprocess data
data <- from_json_dir_data(json_dir) %>%
  mutate(elements = get_elements(name)) %>%
  filter(elements == 2^29) %>%
  mutate(name = get_name(name))

# Validate SEQ_NAME
if (!SEQ_NAME %in% data$name) {
  stop(paste("Error: SEQ_NAME", SEQ_NAME, "not found in the data."))
}

# Separate sequential data
seq_data <- data %>%
  filter(name == SEQ_NAME) %>%
  select(-used_threads) %>%
  mutate(name = factor(name, levels = unique(name))) %>%
  select(name, real_time)

# Remove SEQ_NAME from main dataset
data <- data %>%
  filter(name != SEQ_NAME) %>%
  select(name, real_time, used_threads) %>%
  sort_data_seq_first()

# Compute speedup and efficiency
speedup_data <- data %>%
  mutate(
    speedup = seq_data$real_time / real_time,
    efficiency = speedup / used_threads
  )

min_threads <- min(speedup_data$used_threads)
max_threads <- max(speedup_data$used_threads)
max_speedup <- max(speedup_data$speedup)

palette <- get_palette(speedup_data$name, skip = 1)
shape_values <- get_shapes(speedup_data$name, skip = 1)

# Ideal speedup line
ideal_line_data <- data.frame(
  used_threads = seq(min_threads, max_threads, length.out = 100),
  speedup = seq(min_threads, max_threads, length.out = 100),
  name = "Ideal"
) %>%
  filter(speedup <= max_speedup + 2)

# Ensure name consistency
speedup_data$name <- as.character(speedup_data$name)
ideal_line_data$name <- "Ideal"

# Harmonize factor levels
combined_names <- c("Ideal", unique(speedup_data$name))
speedup_data$name <- factor(speedup_data$name, levels = combined_names)
ideal_line_data$name <- factor(ideal_line_data$name, levels = combined_names)

# Prepare scales
named_palette <- setNames(palette, levels(speedup_data$name)[-1])
color_values <- c("Ideal" = "black", named_palette)
shape_values_all <- c(setNames(shape_values, names(named_palette)), "Ideal" = NA)
linetype_values <- c("Ideal" = "solid", setNames(rep("solid", length(named_palette)), names(named_palette)))

# Final plot with unified aes() and only one legend
p <- ggplot(
  bind_rows(speedup_data, ideal_line_data), # Combine for consistent aesthetics
  aes(x = used_threads, y = speedup, color = name, shape = name, linetype = name)
) +
  geom_line(data = speedup_data, linewidth = 1) +
  geom_point(data = speedup_data, size = 6, stroke = 2) +
  geom_line(data = ideal_line_data, linewidth = 1.6) +
  scale_x_log10(
    breaks = 2^seq(floor(log2(min_threads)), ceiling(log2(max_threads))),
    labels = 2^seq(floor(log2(min_threads)), ceiling(log2(max_threads))),
    name = "#Threads"
  ) +
  scale_color_manual(name = NULL, values = color_values) +
  scale_shape_manual(
    name = NULL, values = shape_values_all,
    guide = guide_legend(override.aes = list(shape = c(shape_values, NA)))
  ) +
  scale_linetype_manual(name = NULL, values = linetype_values) +
  labs(
    title = plot_title,
    y = paste("Speedup (vs ", SEQ_NAME, ")")
  ) +
  theme(
    panel.grid.minor = element_blank(),
    panel.grid.major = element_line(color = "gray", linewidth = 0.25, linetype = "dashed"),
    panel.border = element_rect(color = "black", fill = NA, linewidth = 0.5),
    plot.title = element_text(hjust = 0.5, size = 25, face = "bold"),
    axis.text = element_text(size = 26),
    axis.title = element_text(size = 28),
    legend.text = element_text(size = 20, face = "bold"),
    legend.background = element_rect(fill = alpha("white", 0.75), color = alpha("black", 0.5))
  )

# Reposition legend
reposition_legend(p, "top left", offset = 0.02)

print(speedup_data)

# Optional: interactive plot
# p_load(plotly)
# ggplotly(p)