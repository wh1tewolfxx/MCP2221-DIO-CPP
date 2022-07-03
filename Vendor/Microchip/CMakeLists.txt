message("-- Linking Microchip dll")
add_library(mcp2221_dll_um_x64 mcp2221_dll_um )
set_target_properties(mcp2221_dll_um_x64
	PROPERTIES
	LINKER_LANGUAGE CXX)
add_custom_command(TARGET mcp2221_dll_um_x64 PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/Vendor/Microchip/ $<TARGET_FILE_DIR:mcp2221_dll_um_x64>)
