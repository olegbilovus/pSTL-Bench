install.packages("pacman", repos = "http://cran.us.r-project.org")
library(pacman)
pacman::p_load(rio, ggplot2, tidyverse, lemon)
theme_set(theme_bw())

source("utils.R")

json_dir <- "json_data/speedup_threads/for_each-k1000"
data <- from_json_dir_data(json_dir)

plot_title <- NULL
SEQ_NAME <- "GCC-SEQ"

# Extract the number of elements from the 'name' column
data <- data %>%
  mutate(
    elements = get_elements(name),
  )

# Filter only the rows with 2^30 elements
data <- data %>%
  filter(elements == 2^30)

# Extract the name for the plot
data <- data %>%
  mutate(
    name = get_name(name),
  )

# Get the SEQ data and remove from the main data. If SEQ_NAME is not in the data, error
if (!SEQ_NAME %in% data$name) {
  stop(paste("Error: SEQ_NAME", SEQ_NAME, "not found in the data."))
}
seq_data <- data %>%
  filter(name == SEQ_NAME) %>%
  select(-used_threads) %>%
  mutate(
    name = factor(name, levels = unique(name)),
  ) %>%
  select(name, real_time)

# Remove the SEQ_NAME from the data
data <- data %>%
  filter(name != SEQ_NAME) %>%
  mutate(
    name = factor(name, levels = unique(name)),
  )

# Select relevant columns
data <- data %>%
  select(name, real_time, used_threads)

# Order the data by name
data <- data %>%
  mutate(name = factor(name, levels = unique(name)))

# Calculate speedup
speedup_data <- data %>%
  mutate(
    speedup = seq_data$real_time / real_time,
  )

shape_values <- get_shapes(speedup_data$name)

min_threads <- min(speedup_data$used_threads)
max_threads <- max(speedup_data$used_threads)
max_speedup <- max(speedup_data$speedup)

# Create a data frame for the ideal speedup line (y = x)
ideal_line_data <- data.frame(
  used_threads = seq(min_threads, max_threads, length.out = 100), # Generate x values
  speedup = seq(min_threads, max_threads, length.out = 100) # Ideal speedup (y = x)
) %>%
  filter(speedup <= max_speedup + 2) # Limit the ideal line to max_speedup

p <- ggplot(speedup_data, aes(x = used_threads, y = speedup, color = name, shape = name)) +
  geom_line(linewidth = 0.7) +
  geom_point(size = 3, stroke = 1) +
  # Add the ideal speedup line (y = x)
  geom_line(data = ideal_line_data, aes(x = used_threads, y = speedup), inherit.aes = FALSE, color = "black") +
  scale_x_log10( # Use a logarithmic scale for the x-axis
    breaks = 2^seq(floor(log2(min_threads)), ceiling(log2(max_threads))), # Powers of 2
    labels = 2^seq(floor(log2(min_threads)), ceiling(log2(max_threads))), # Format x-axis labels as powers of 2
    name = "#Threads"
  ) +
  scale_color_discrete(name = NULL) + # Remove the legend title for color
  scale_shape_manual(
    name = NULL, # Remove the legend title for shape
    values = shape_values,
  ) +
  labs(
    title = plot_title,
    y = paste("Speedup (vs ", SEQ_NAME, ")"),
  ) +
  theme(
    panel.grid.minor = element_blank(), # Remove minor grid lines
    panel.grid.major = element_line(color = "gray", linewidth = 0.25, linetype = "dashed"),
    legend.background = element_rect(fill = scales::alpha("white", 0.75), color = scales::alpha("black", 0.5)), # Add a border around the legend
    panel.border = element_rect(color = "black", fill = NA, linewidth = 0.5), # Add a border around the plot
    plot.title = element_text(hjust = 0.5) # Center the title
  )

reposition_legend(p, "top left", offset = 0.02)

# interactive plot
# pacman::p_load(plotly)
# ggplotly(p)