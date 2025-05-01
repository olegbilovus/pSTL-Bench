if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel" AND
        NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "IntelLLVM")
    message(WARNING "To use the ONE_DPL backend, make sure you use an Intel compiler. Your compiler ID: ${CMAKE_CXX_COMPILER_ID}")
endif()

add_compile_definitions(PSTL_BENCH_USE_GPU)
add_compile_definitions(PSTL_BENCH_USE_ONE_DPL)

add_compile_definitions(PSTL_BENCH_BACKEND="ONE_DPL")

# Find Intel oneAPI DPC++ Library (oneDPL)
find_package(oneDPL REQUIRED)

if (NOT TARGET oneDPL)
    message(FATAL_ERROR "oneDPL target not found")
else ()
    message(STATUS "oneDPL target found")
    list(APPEND LINK_LIBRARIES oneDPL)
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsycl")