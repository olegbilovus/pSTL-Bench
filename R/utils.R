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

get_shapes <- function(data) {
  # Dynamically generate shapes based on the number of unique names
  unique_data <- unique(data)
  num_unique_data <- length(unique_data)

  shape_values <- c(15:25, 0:20)[1:num_unique_data]

  return(shape_values)
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
  }
  
  return(data)
}