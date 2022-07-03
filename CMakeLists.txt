# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("MCP2221-DIO")

#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")


# Include sub-projects.
add_subdirectory ("MCP2221-DIO")

include_directories("${PROJECT_SOURCE_DIR}/Vendor/Microchip") 

add_subdirectory("${PROJECT_SOURCE_DIR}/Vendor/Microchip")


