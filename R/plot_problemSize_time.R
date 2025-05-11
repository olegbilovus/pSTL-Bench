install.packages("pacman", repos = "http://cran.us.r-project.org")
library(pacman)
pacman::p_load(rio, ggplot2, tidyverse, lemon)
theme_set(theme_bw())

source("utils.R")

json_dir <- "json_data/problemSize_time/for_each-k1000"
data <- from_json_dir_data(json_dir)

plot_title <- NULL

# Extract the number of elements from the 'name' column
data <- data %>%
  mutate(
    elements = get_elements(name),
  )

# Extract the name for the plot
data <- data %>%
  mutate(
    name = get_name(name),
  )

# Select relevant columns
data <- data %>%
  select(name, elements, real_time)

print(data)

# Dynamically generate shapes based on the number of unique names
unique_names <- unique(data$name)
num_unique_names <- length(unique_names)

shape_values <- c(15:25, 0:20)[1:num_unique_names]


# Plot the data with log2 for x-axis and log10 for y-axis, with custom labels
p <- ggplot(data, aes(x = log2(elements), y = log10(real_time), color = name, shape = name)) +
  geom_line(linewidth = 0.7) +
  geom_point(size = 3, stroke = 1) +
  scale_x_continuous(
    breaks = seq(0, max(log2(as.numeric(data$elements))), by = 5), # Add more x-axis labels
    labels = scales::math_format(2^.x), # Format x-axis labels as 2^
    name = "Problem size (#elements)"
  ) +
  scale_y_continuous(
    breaks = seq(0, max(log10(data$real_time)), by = 2), # Add more y-axis labels
    labels = scales::math_format(10^.x), # Format y-axis labels as 10^
    name = "Time (ns)"
  ) +
  scale_color_discrete(name = NULL) + # Remove the legend title for color
  scale_shape_manual(
    name = NULL, # Remove the legend title for shape
    values = shape_values, # Dynamically assign shapes
  ) +
  labs(title = plot_title) +
  theme(
    panel.grid.minor = element_blank(), # Remove minor grid lines
    panel.grid.major = element_line(color = "gray", linewidth = 0.25, linetype = "dashed"), # Minor grid lines
    legend.background = element_rect(fill = scales::alpha("white", 0.75), color = scales::alpha("black", 0.5)), # Add a border around the legend
    panel.border = element_rect(color = "black", fill = NA, linewidth = 0.5), # Add a border around the plot
    plot.title = element_text(hjust = 0.5) # Center the title
  )

reposition_legend(p, "top left", offset = 0.02)

# interactive plot
# pacman::p_load(plotly)
# ggplotly(p)
