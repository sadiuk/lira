

set(LIRA_GRAPHICS_SOURCES
	export/graphics/IGraphicsContext.ixx
	
	impl/graphics/IGraphicsContext.cppm
	impl/graphics/platform/OpenGL/GraphicsContextOpenGL.ixx
	impl/graphics/platform/OpenGL/GraphicsContextOpenGL.cppm
	)

set(LIRA_UI_SOURCES
	export/ui/IWindow.ixx

	impl/ui/platform/GLFW/WindowGLFW.ixx
	impl/ui/platform/GLFW/WindowGLFW.cppm
)

set(LIRA_THREAD_SOURCES

	impl/thread/IThread.ixx
	impl/thread/IThreadRequestProcessor.ixx
)

add_library	(lira 
			${LIRA_GRAPHICS_SOURCES} 
			${LIRA_UI_SOURCES} 
			${LIRA_THREAD_SOURCES}
			)
target_include_directories(lira PUBLIC 
	${LIRA_ROOT_PATH}/src
	)
