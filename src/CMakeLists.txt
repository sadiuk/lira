

set(LIRA_GRAPHICS_SOURCES
	export/graphics/IGraphicsContext.ixx
	export/graphics/IGraphicsPipeline.ixx
	export/graphics/IComputePipeline.ixx
	export/graphics/IPipeline.ixx
	export/graphics/IShader.ixx
	export/graphics/IBuffer.ixx
	export/graphics/ITexture.ixx
	export/graphics/IFramebuffer.ixx
	export/graphics/GraphicsCommon.ixx
	
	impl/graphics/IGraphicsContext.cppm
	impl/graphics/platform/OpenGL/GraphicsContextOpenGL.ixx
	impl/graphics/platform/OpenGL/GraphicsContextOpenGL.cppm
	impl/graphics/platform/OpenGL/GraphicsPipelineOpenGL.ixx
	impl/graphics/platform/OpenGL/GraphicsPipelineOpenGL.cppm
	impl/graphics/platform/OpenGL/ComputePipelineOpenGL.ixx
	impl/graphics/platform/OpenGL/PipelineOpenGL.ixx
	impl/graphics/platform/OpenGL/PipelineOpenGL.cppm
	impl/graphics/platform/OpenGL/ComputePipelineOpenGL.cppm
	impl/graphics/platform/OpenGL/ShaderOpenGL.ixx
	impl/graphics/platform/OpenGL/ShaderOpenGL.cppm
	impl/graphics/platform/OpenGL/BufferOpenGL.ixx
	impl/graphics/platform/OpenGL/BufferOpenGL.cppm
	impl/graphics/platform/OpenGL/TextureOpenGL.ixx
	impl/graphics/platform/OpenGL/TextureOpenGL.cppm
	impl/graphics/platform/OpenGL/FramebufferOpenGL.ixx
	impl/graphics/platform/OpenGL/FramebufferOpenGL.cppm
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

set(LIRA_FS_SOURCES
	export/fs/IFile.ixx
	export/fs/IFilesystem.ixx

	impl/fs/platform/std/FileSTD.ixx
	impl/fs/platform/std/FileSTD.cppm
	impl/fs/platform/std/FilesystemSTD.ixx
	impl/fs/platform/std/FilesystemSTD.cppm
)

set(LIRA_MATH_SOURCES
	export/math/Types.ixx
	export/math/Vector.ixx
	export/math/Matrix.ixx
	export/math/MathCommon.ixx
	export/math/MathOperations.ixx
)

set(LIRA_CORE_SOURCES
	export/core/Buffer.ixx
	export/core/CoreCommon.ixx

)

add_library	(lira 
			${LIRA_GRAPHICS_SOURCES} 
			${LIRA_UI_SOURCES} 
			${LIRA_THREAD_SOURCES}
			${LIRA_MATH_SOURCES}
			${LIRA_FS_SOURCES}
			${LIRA_CORE_SOURCES}
			)
target_include_directories(lira PUBLIC 
	${LIRA_ROOT_PATH}/src
	)
