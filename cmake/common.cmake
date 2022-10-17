function( createEXE EXE_NAME SOURCES )
	project(${EXE_NAME})
	set( _SOURCES ${SOURCES} ${ARGN} )
	add_executable(${EXE_NAME} main.cpp ${_SOURCES})
	add_dependencies(${EXE_NAME} lira)
	#target_include_directories(${EXE_NAME}
	#	PUBLIC ../../src
	#)
	set_property(TARGET ${EXE_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/examples/${EXE_NAME}")
	target_link_libraries(${EXE_NAME} lira)
	find_package(OpenGL REQUIRED)
	target_link_libraries(${EXE_NAME} ${OPENGL_LIBRARIES})
endfunction()