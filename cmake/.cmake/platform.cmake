# Windows
if(WIN32)
    ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN)

    MESSAGE(STATUS "[GooseUI] -- OS: Windows")
    MESSAGE(STATUS "[GooseUI] -- Display Service: Win32")

    LIST(APPEND GOOSEUI_LIBRARY "dwrite")
    LIST(
        APPEND GOOSEUI_SRC
        "src/platform/win32_window.cpp"
    )
endif()

# MacOS
if(APPLE)
    MESSAGE(STATUS "[GooseUI] -- OS: MacOS")
    MESSAGE(FATAL_ERROR "[GooseUI] -- honk (Unsupported)")
endif()

# Unix Or Other
if(UNIX AND NOT APPLE)
    MESSAGE(STATUS "[GooseUI] -- OS: UNIX or Other")

    if(GOOSEUI_XORG_SUPPORT)
        MESSAGE(STATUS "[GooseUI] -- Display Service: X11")

        FIND_PACKAGE(X11 REQUIRED)

        LIST(APPEND GOOSEUI_INCLUDE "${X11_INCLUDE_DIR}")
        LIST(APPEND GOOSEUI_LIBRARY "${X11_LIBRARIES}")
        LIST(APPEND GOOSEUI_BUILD_FLAGS "X11")
        LIST(
            APPEND GOOSEUI_SRC
            "src/platform/x11_window.cpp"
        )
        
        add_compile_definitions(GOOSEUI_XORG_SUPPORT)
    endif()

    if(GOOSEUI_WAYLAND_SUPPORT)
        MESSAGE(STATUS "[GooseUI] -- Display Service: Wayland")

        FIND_PACKAGE(Wayland REQUIRED)

        LIST(APPEND GOOSEUI_INCLUDE "${WAYLAND_CLIENT_DIR}")
        LIST(APPEND GOOSEUI_LIBRARY "${WAYLAND_CLIENT_LIB}")
        LIST(APPEND GOOSEUI_BUILD_FLAGS "wayland-client")
        LIST(
            APPEND GOOSEUI_SRC
        )
        
        add_compile_definitions(GOOSEUI_WAYLAND_SUPPORT)
    endif()
    
endif()