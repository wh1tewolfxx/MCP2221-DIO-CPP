# CMakeList.txt : CMake project for MCP2221-DIO, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
# Add source to this project's executable.
add_executable (MCP2221-DIO "MCP2221-DIO.cpp"  "MCP2221-DIO.h")
target_link_libraries(MCP2221-DIO PUBLIC mcp2221_dll_um_x64)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MCP2221-DIO PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
