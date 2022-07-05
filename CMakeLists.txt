# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.

cmake_minimum_required (VERSION 3.8)
project ("MCP2221-DIO")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")


link_directories(${CMAKE_SOURCE_DIR}/Vendor/Microchip)
# Include sub-projects.

add_subdirectory ("Vendor/Microchip")

add_library(MCP2221_LIB SHARED IMPORTED)

# Add source to this project's executable.
add_executable (MCP2221-DIO "main.cpp"  "main.h")

add_custom_command(TARGET MCP2221-DIO POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/Vendor/Microchip/mcp2221_dll_um_x64.dll"      # <--this is in-file
        $<TARGET_FILE_DIR:MCP2221-DIO>)         

add_custom_command(TARGET MCP2221-DIO PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/Vendor/Microchip ${CMAKE_BINARY_DIR}/Vendor/Microchip
)
target_link_libraries(MCP2221-DIO PUBLIC mcp2221_dll_um_x64.lib)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MCP2221-DIO PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

