cmake_minimum_required(VERSION 3.10.0)
project(GooseUI VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

# Display Services - OPTIONS
    option(GOOSEUI_SUPPORT_WAYLAND "Includes Wayland Support" ON)
    option(GOOSEUI_SUPPORT_XORG "Includes Legacy X11 Support" ON)
    option(GOOSEUI_SUPPORT_WIN32 "Includes Win32API Support" ON)
    #option(GOOSEUI_SUPPORT_MACOS "Includes what ever apple uses" OFF)

# Graphical API's - OPTIONS
    #option(GOOSEUI_SUPPORT_OPENGL "Includes Inbedding OpenGL" OFF)
    #option(GOOSEUI_SUPPORT_VULKAN "Includes Inbedding Vulkan" OFF)

# Extra - OPTIONS
    option(GOOSEUI_BUILD_TESTS "Builds included examples & test applications" ON)

include("${CMAKE_SOURCE_DIR}/cmake/.cmake/core.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/.cmake/widgets.cmake")

# Determin external libs
if(WIN32)
    message(STATUS "[GooseUI] -- Detected OS: Win32")

    if(GOOSEUI_SUPPORT_WIN32)
    message(STATUS "[GooseUI] -- Display Service Enabled: WindowsAPI")
    set(GOOSEUI_HONK true)

    include("${CMAKE_SOURCE_DIR}/cmake/.cmake/platforms/win32.cmake" REQUIRED)
    add_compile_definitions(GooseUI_UseWin32)
    endif()

endif()

if(APPLE)
    message(STATUS "[GooseUI] -- Detected OS: Apple")
    message(FATAL_ERROR "[GooseUI] -- honk (Unsupported) :<")
endif()

if(UNIX AND NOT APPLE)
    message(STATUS "[GooseUI] -- Detected OS: UNIX")

    find_package(Freetype REQUIRED)
    list(APPEND GOOSEUI_INCLUDE "${FREETYPE_INCLUDE_DIR}")
    list(APPEND GOOSEUI_LIBRARY "${FREETYPE_LIB}")
    list(APPEND GOOSEUI_FLAGS "fontconfig" "freetype2")

    if(GOOSEUI_SUPPORT_XORG)
        message(STATUS "[GooseUI] -- Display Service Enabled: X11")
        set(GOOSEUI_HONK true)

        find_package(X11 REQUIRED)
        find_package(Xft REQUIRED)

        list(APPEND GOOSEUI_INCLUDE "${X11_INCLUDE_DIR}" "${XFT_INCLUDE_DIR}")
        list(APPEND GOOSEUI_LIBRARY "${X11_LIBRARIES}" "${XFT_LIB}")
        list(APPEND GOOSEUI_FLAGS "X11" "xft")

        include("${CMAKE_SOURCE_DIR}/cmake/.cmake/platforms/xorg.cmake" REQUIRED)
        add_compile_definitions(GooseUI_UseXorg)
    endif()

    if(GOOSEUI_SUPPORT_WAYLAND)
        message(STATUS "[GooseUI] -- Display Service Enabled: Wayland")
        set(GOOSEUI_HONK true)

        find_package(Wayland REQUIRED)

        list(APPEND GOOSEUI_INCLUDE "${WAYLAND_INCLUDE_DIR}")
        list(APPEND GOOSEUI_LIBRARY "${WAYLAND_CLIENT_LIB}")
        list(APPEND GOOSEUI_FLAGS "wayland-client")

        include("${CMAKE_SOURCE_DIR}/cmake/.cmake/platforms/wayland.cmake" REQUIRED)
        add_compile_definitions(GooseUI_UseWayland)
    endif()

endif()

if(NOT GOOSEUI_HONK)
    message(FATAL_ERROR "[GooseUI] -- Faild to HONK (No Display Service)")
endif()

# GooseLib
set(GOOSEUI_SRC ${GOOSEUI_COREFILES} ${GOOSEUI_WIDGETS} ${GOOSEUI_PLATFORM})
add_library(${PROJECT_NAME} ${GOOSEUI_SRC} "include")

target_include_directories(${PROJECT_NAME} PRIVATE "include" ${GOOSEUI_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GOOSEUI_LIBRARY})
target_link_directories(${PROJECT_NAME} PRIVATE ${GOOSEUI_FLAGS})

if(GOOSEUI_BUILD_TESTS)
    add_subdirectory("tests")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "GooseUI" VERSION ${PROJECT_VERSION} SOVERSION "0" FOLDER "GooseUI")