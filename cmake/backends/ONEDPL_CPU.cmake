if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel" AND
        NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "IntelLLVM")
    message(WARNING "To use the ONEDPL_CPU backend, make sure you use an Intel compiler. Your compiler ID: ${CMAKE_CXX_COMPILER_ID}")
endif()

add_compile_definitions(PSTL_BENCH_USE_ONEDPL)

add_compile_definitions(PSTL_BENCH_BACKEND="ONEDPL_CPU")

# Use TBB as the backend for oneDPL
message(STATUS "Using TBB as the backend for oneDPL")
set(ONEDPL_BACKEND tbb)
set(ONEDPL_PAR_BACKEND tbb)
add_compile_definitions(PSTL_BENCH_USE_TBB)

# Find Intel oneAPI DPC++ Library (oneDPL)
find_package(oneDPL REQUIRED)

if (NOT TARGET oneDPL)
    message(FATAL_ERROR "oneDPL target not found")
else ()
    message(STATUS "oneDPL target found")
    list(APPEND LINK_LIBRARIES oneDPL)
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsycl")