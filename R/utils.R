library(jsonlite)
library(readr)

from_json_dir_data <- function(json_dir) {
# Function to import JSON data from a directory
  json_files <- list.files(json_dir, pattern = "\\.json$", full.names = TRUE, recursive = TRUE)
  data_list <- list()

  for (json_file in json_files) {
    json_data <- fromJSON(json_file)

    df <- as.data.frame(json_data$benchmarks)

    # Append the data frame to the list
    data_list[[length(data_list) + 1]] <- df
  }

  # Combine all data frames into one, filling missing columns with NA
  data <- bind_rows(data_list)

  return(data)
}

get_name <- function(name) {
  # Extract the name for the plot
  name <- str_split_fixed(name, "/", 2)[, 1]
  return(name)
}

get_elements <- function(name) {
  # Extract the number of elements from the 'name' column
  elements <- as.integer(str_split_fixed(name, "/", 5)[, 4])
  return(elements)
}

get_algorithm <- function(name, kernel_its) {
  # Extract the algorithm name from the 'name' column and append the kernel_its if not NA
  algorithm <- str_split_fixed(str_split_fixed(name, "/", 3)[, 2], "::", 2)[, 2]
  algorithm <- ifelse(!is.na(kernel_its), paste(algorithm, "-k", kernel_its, sep = ""), algorithm)
  return(algorithm)
}

get_shapes <- function(data, skip = 0) {
  # Dynamically generate shapes based on the number of unique names
  unique_data <- unique(data)
  num_unique_data <- length(unique_data)
  all_shapes <- c(15:25, 0:20)
  shape_values <- all_shapes[(1 + skip):(num_unique_data + skip)]

  return(shape_values)
}

get_palette <- function(data, skip = 0) {
  # Dynamically generate a color palette and optionally skip the first color (e.g., red)
  unique_data <- unique(data)
  num_unique_data <- length(unique_data)
  pal <- scales::hue_pal()(num_unique_data + skip)
  pal <- pal[(1 + skip):(num_unique_data + skip)]
  return(pal)
}

get_seq_name <- function() {
  return ("GNU-SEQ")
  
}

sort_data_seq_first <- function(data) {
  # Sort the data so that the sequential algorithm is first
  seq_name <- get_seq_name()
  
  # Check if the sequential name exists in the data
  if (seq_name %in% data$name) {
    # Move the sequential algorithm to the first position
    data <- data %>%
      mutate(name = factor(name, levels = c(get_seq_name(), sort(unique(name)[!unique(name) %in% get_seq_name()]))))
  } else {
    # If the sequential name does not exist, just sort the data by name
    data <- data %>%
      mutate(name = factor(name, levels = sort(unique(name))))
  }
  
  return(data)
}

add_ideal_annotation <- function(min_threads, max_threads, max_speedup, 
                                position = c("topright", "topleft"), 
                                label = "Ideal", 
                                seg_len = 0.3, 
                                y_offset = 0.01, 
                                size = 8) {
  position <- match.arg(position)
  # Helper for log interpolation
  log_interp <- function(a, b, frac) exp(log(a) + frac * (log(b) - log(a)))
  if (position == "topright") {
    # Place segment and text at 80% and 90% of the log10 axis range
    x_start <- log_interp(min_threads, max_threads, 0.80)
    x_end   <- log_interp(min_threads, max_threads, 0.90)
    x_text  <- log_interp(min_threads, max_threads, 0.93)
    y_pos   <- max_speedup * (1 + y_offset)
    hjust   <- 0
  } else if (position == "topleft") {
    x_start <- min_threads * (1 + 0.05)
    x_end   <- min_threads * (1 + seg_len)
    x_text  <- x_end
    y_pos   <- max_speedup * (1 + y_offset)
    hjust   <- 0
  }
  list(
    annotate("segment",
      x = x_start, xend = x_end,
      y = y_pos, yend = y_pos,
      color = "black", linewidth = 2
    ),
    annotate("text",
      x = x_text, y = y_pos,
      label = label, hjust = hjust, vjust = 0.5, size = size, fontface = "bold", color = "black"
    )
  )
}