library(jsonlite)
library(readr)

# Function to import JSON data from a directory
from_json_dir_data <- function(json_dir) {
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

get_algorithm <- function(name) {
  # Extract the algorithm name from the 'name' column
  algorithm <- str_split_fixed(str_split_fixed(name, "/", 3)[, 2], "::", 2)[, 2]
  return(algorithm)
}