if (!requireNamespace("pacman", quietly = TRUE)) install.packages("pacman", repos = "http://cran.us.r-project.org")
pacman::p_load(ggplot2, tidyverse)

# Set theme
theme_set(theme_bw())

# Load helper functions
source("utils.R")

# Define paths and constants
json_dir <- "json_data/problemSize_time/for_each-k1"
plot_title <- NULL

gpu_names <- c("IntelLLVM-ONEDPL_GPU", "NVHPC-CUDA")
# Load and preprocess data
data <- from_json_dir_data(json_dir) %>%
  mutate(elements = get_elements(name)) %>%
  mutate(name = get_name(name)) %>%
  # Comment out the following line if you want to filter out GPU data
  filter(!name %in% gpu_names) %>%
  select(name, elements, real_time) %>%
  sort_data_seq_first()

palette <- get_palette(data$name)
shape_values <- get_shapes(data$name)


# Plot the data with log2 for x-axis and log10 for y-axis, with custom labels
p <- ggplot(
  data,
  aes(x = log2(elements), y = log10(real_time), color = name, shape = name)
) +
  geom_line(linewidth = 1) +
  geom_point(size = 6, stroke = 2) +
  scale_x_continuous(
    breaks = seq(0, max(log2(as.numeric(data$elements))), by = 5), # Add more x-axis labels
    labels = scales::math_format(2^.x), # Format x-axis labels as 2^
  ) +
  scale_y_continuous(
    breaks = seq(0, max(log10(data$real_time)), by = 2), # Add more y-axis labels
    labels = scales::math_format(10^.x), # Format y-axis labels as 10^
  ) +
  scale_color_manual(
    name = NULL,
    values = palette,
  ) +
  scale_shape_manual(
    name = NULL,
    values = shape_values,
    guide = guide_legend(
      override.aes = list(size = 4.5) # smaller shape size in the legend
    )
  ) +
  labs(
    title = plot_title,
    x = "Problem size (#elements)",
    y = "Time (ns)"
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
