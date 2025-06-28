# Load required packages
if (!requireNamespace("pacman", quietly = TRUE)) install.packages("pacman", repos = "http://cran.us.r-project.org")
pacman::p_load(ggplot2, tidyverse)

# Set theme
theme_set(theme_bw())

# Load helper functions
source("utils.R")

# Define paths and constants
json_dir <- "json_data/speedup_threads/for_each-k1"
plot_title <- NULL
SEQ_NAME <- get_seq_name()

# Load and preprocess data
data <- from_json_dir_data(json_dir) %>%
  mutate(elements = get_elements(name)) %>%
  filter(elements == 2^29) %>% # Filter for a specific problem size
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
  select(name, real_time, used_threads)

# Compute speedup and efficiency
speedup_data <- data %>%
  mutate(
    speedup = seq_data$real_time / real_time,
    efficiency = speedup / used_threads
  ) %>%
  sort_data_seq_first()

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
speedup_data$name <- factor(speedup_data$name, levels = unique(speedup_data$name), sort(unique(speedup_data$name)))
ideal_line_data$name <- factor(ideal_line_data$name, levels = combined_names)

# Prepare scales
named_palette <- setNames(palette, levels(speedup_data$name))
color_values <- c("Ideal" = "black", named_palette)
shape_values_all <- c(setNames(shape_values, names(named_palette)), "Ideal" = NA)

# Plot
p <- ggplot(
  bind_rows(speedup_data, ideal_line_data),
  aes(x = used_threads, y = speedup, color = name, shape = name)
) +
  geom_line(data = speedup_data, linewidth = 1) +
  geom_point(data = speedup_data, size = 6, stroke = 2) +
  geom_line(data = ideal_line_data, linewidth = 1) +
  scale_x_log10(
    breaks = 2^seq(floor(log2(min_threads)), ceiling(log2(max_threads))),
    labels = 2^seq(floor(log2(min_threads)), ceiling(log2(max_threads))),
  ) +
  scale_color_manual(
    name = NULL,
    values = color_values
  ) +
  scale_shape_manual(
    name = NULL,
    values = shape_values_all,
    guide = guide_legend(
      override.aes = list(size = 4.5) # smaller shape size in the legend
    )
  ) +
  labs(
    title = plot_title,
    x = "#Threads",
    y = paste("Speedup (vs", paste(SEQ_NAME, ")", sep = ""))
  ) +
  get_theme(legend_position = "top-left") # Adjust legend position: "top-right" or "top-left"

plot_width <- 8
plot_height <- 6

show_plot_with_size(p, width = plot_width, height = plot_height)

filename <- get_plot_filename(json_dir)
save_to_cairo_pdf(p, filename, width = plot_width, height = plot_height)

# Save the plot to a PDF file and close the window if open
dev.off()
rm(list = ls()) # Clean up the environment
