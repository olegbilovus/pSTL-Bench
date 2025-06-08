if (!requireNamespace("pacman", quietly = TRUE)) install.packages("pacman", repos = "http://cran.us.r-project.org")
pacman::p_load(jsonlite, dplyr)

from_json_dir_data <- function(json_dir) {
  # Import and combine JSON benchmark data from a directory
  json_files <- list.files(json_dir, pattern = "\\.json$", full.names = TRUE, recursive = TRUE)

  data_list <- lapply(json_files, function(file) {
    tryCatch({
      json_data <- jsonlite::fromJSON(file)
      as.data.frame(json_data$benchmarks)
    }, error = function(e) {
      stop(sprintf("Error reading file '%s': %s", file, e$message))
    })
  })

  data <- dplyr::bind_rows(data_list)
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
  return("GNU-SEQ")
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

get_theme <- function(legend_position = "top-right") {
  # check if the legend position is valid
  if (!legend_position %in% c("top-left", "top-right")) {
    stop("Invalid legend position. Use 'top-left' or 'top-right'.")
  }

  if (legend_position == "top-left") {
    legend_position_inside <- c(0.02, 0.98) # top-left corner
    legend_justification <- c("left", "top")
  } else {
    legend_position_inside <- c(0.98, 0.98) # top-right corner
    legend_justification <- c("right", "top")
  }

  # Define the ggplot theme
  theme(
    panel.grid.minor = element_blank(),
    panel.grid.major = element_line(color = "gray", linewidth = 0.25, linetype = "dashed"),
    panel.border = element_rect(color = "black", fill = NA, linewidth = 0.5),
    plot.title = element_text(hjust = 0.5, size = 25, face = "bold"),
    axis.line = element_blank(),
    axis.ticks = element_line(color = "black"),
    axis.ticks.length = unit(-0.25, "cm"),
    axis.text = element_text(size = 26, colour = "black"),
    axis.title = element_text(size = 28),
    legend.text = element_text(size = 22),
    legend.key.width = unit(1, "cm"), # helps prevent label crowding
    legend.key.height = unit(0.4, "cm"), # keep key boxes compact
    legend.margin = margin(5, 5, 5, 5),
    legend.position = "inside",
    legend.position.inside = legend_position_inside,
    legend.justification = legend_justification,
    legend.background = element_rect(
      fill = alpha("white", 0.5),
      color = "black",
      linewidth = 0.5
    )
  )
}

show_plot_with_size <- function(p, width = 6, height = 8) {
  if (.Platform$OS.type == "windows") {
    windows(width = width, height = height)
  } else if (Sys.info()[["sysname"]] == "Linux") {
    x11(width = width, height = height)
  } else if (Sys.info()[["sysname"]] == "Darwin") {
    quartz(width = width, height = height)
  } else {
    warning("Unknown platform. Cannot open custom-size plot window.")
  }

  print(p)
}

get_plot_filename <- function(json_dir, ext = ".pdf") {
  # Normalize path and split into components
  dir_parts <- strsplit(json_dir, .Platform$file.sep)[[1]]

  # Remove any empty segments (e.g. from trailing slashes)
  dir_parts <- dir_parts[dir_parts != ""]

  # Get the last two components of the path
  last_two <- tail(dir_parts, 2)

  # Combine them with a dash
  base_name <- paste(last_two, collapse = "-")

  # Return the final filename
  paste0(base_name, ext)
}

save_to_cairo_pdf <- function(p, filename, width = 6, height = 8, dir = "plots") {
  # Save the plot to a Cairo PDF file
  if (!dir.exists(dir)) {
    dir.create(dir, recursive = TRUE)
  }
  filename <- file.path(dir, filename)

  cairo_pdf(filename, width = width, height = height)
  print(p)
  dev.off()
}
