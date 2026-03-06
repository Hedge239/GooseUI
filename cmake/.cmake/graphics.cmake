# OpenGL
if(GOOSEUI_INCLUDE_OPENGL)
    SET(OpenGL_GL_PREFERENCE GLVND)
    FIND_PACKAGE(OpenGL)

    if(OPENGL_FOUND)
        MESSAGE(STATUS "[GooseUI] -- OpenGL Enabled")
    
        LIST(APPEND GOOSEUI_LIBRARY "OpenGL::GL")
        LIST(
            APPEND GOOSEUI_SRC
            "src/graphics/GL/glLoader.cpp"
            "src/graphics/GL/glRenderer.cpp"
        )

        ADD_COMPILE_DEFINITIONS(GOOSEUI_HAS_OPENGL)
    endif()
endif()

# Vulkan
if(GOOSEUI_INCLUDE_VULKAN)
    FIND_PACKAGE(Vulkan)

    if(VULKAN_FOUND)
        MESSAGE(STATUS "[GooseUI] -- Vulkan Enabled")

        LIST(APPEND GOOSEUI_LIBRARY "Vulkan::Vulkan")
        LIST(
            APPEND GOOSEUI_SRC
        )

        ADD_COMPILE_DEFINITIONS(GOOSEUI_HAS_VULKAN)
    endif()
endif()

# FreeType
if(UNIX OR APPLE)
    FIND_PACKAGE(Freetype REQUIRED)
    MESSAGE(STATUS "[GooseUI] -- Using FreeType2")

    LIST(APPEND GOOSEUI_LIBRARY Freetype::Freetype)
    LIST(
        APPEND GOOSEUI_SRC
    )
endif()