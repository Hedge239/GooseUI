cmake_minimum_required(VERSION 3.10.0)
project(GooseUI VERSION 0.0.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

# ------------------------------- Options -------------------------------

option(GOOSEUI_USE_OPENGL "Use OpenGL" ON)
option(GOOSEUI_USE_VULKAN "Use Vulkan" OFF)

option(GOOSEUI_XORG_SUPPORT "Legacy X11 Support" ON)
option(GOOSEUI_INSTALL "ExportTargets" ON)
option(GOOSEUI_BUILD_EXAMPLES "Builds included examples & test applications" ON)

# ------------------------------- External Libs -------------------------------

include("${CMAKE_SOURCE_DIR}/cmake/.cmake/core.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/.cmake/widgets.cmake")
# Graphic Services
if(GOOSEUI_USE_OPENGL)
    find_package(OpenGL)

    if(OPENGL_FOUND)
        message(STATUS "[GooseUI] -- OpenGL Detected")
        set(GooseUI_HasGraphicService true)
    
        list(APPEND GOOSEUI_LIBRARY "OpenGL::GL")
        include("${CMAKE_SOURCE_DIR}/cmake/.cmake/graphics/OpenGL.cmake" REQUIRED)

        add_compile_definitions(GOOSEUI_ENABLE_OPENGL)
    endif()
endif()

if(GOOSEUI_USE_VULKAN)
    find_package(Vulkan)

    if(VULKAN_FOUND)
        message(STATUS "[GooseUI] -- Vulkan Detected")
        set(GooseUI_HasGraphicService true)

        list(APPEND GOOSEUI_LIBRARY "Vulkan::Vulkan")
        include("${CMAKE_SOURCE_DIR}/cmake/.cmake/graphics/vulkan.cmake" REQUIRED)

        add_compile_definitions(GOOSEUI_ENABLE_VULKAN)
    endif()
endif()

# Display Services
if(WIN32)
    message(STATUS "[GooseUI] -- OS: Windows")
    message(STATUS "[GooseUI] -- Display Service: windows.h")

    include("${CMAKE_SOURCE_DIR}/cmake/.cmake/platforms/win32.cmake" REQUIRED)
endif()

if(APPLE)
    message(STATUS "[GooseUI] -- OS: MacOS")
    message(FATAL_ERROR "[GooseUI] -- honk (Unsupported)")
endif()

if(UNIX AND NOT APPLE)
    message(STATUS "[GooseUI] -- OS: UNIX")

    if(GOOSEUI_XORG_SUPPORT)
        message(STATUS "[GooseUI] -- Display Service: X11")

        find_package(X11 REQUIRED)

        list(APPEND GOOSEUI_INCLUDE "${X11_INCLUDE_DIR}")
        list(APPEND GOOSEUI_LIBRARY "${X11_LIBRARIES}")
        list(APPEND GOOSEUI_FLAGS "X11")

        include("${CMAKE_SOURCE_DIR}/cmake/.cmake/platforms/xorg.cmake" REQUIRED)
        add_compile_definitions(GooseUI_xorgSupported)
    endif()

    message(STATUS "[GooseUI] -- Display Service: Wayland")

    find_package(Wayland REQUIRED)

    list(APPEND GOOSEUI_INCLUDE "${WAYLAND_INCLUDE_DIR}")
    list(APPEND GOOSEUI_LIBRARY "${WAYLAND_CLIENT_LIB}")
    list(APPEND GOOSEUI_FLAGS "wayland-client")

    include("${CMAKE_SOURCE_DIR}/cmake/.cmake/platforms/wayland.cmake" REQUIRED)
endif()

# ------------------------------- Create Lib -------------------------------

set(GOOSEUI_SRC ${GOOSEUI_COREFILES} ${GOOSEUI_WIDGETS} ${GOOSEUI_PLATFORM})
add_library(${PROJECT_NAME} ${GOOSEUI_SRC} "include")

target_include_directories(${PROJECT_NAME} PRIVATE "include" ${GOOSEUI_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GOOSEUI_LIBRARY})
target_link_directories(${PROJECT_NAME} PRIVATE ${GOOSEUI_FLAGS})

if(GOOSEUI_BUILD_EXAMPLES)
    add_subdirectory("tests")
endif()

if(GOOSEUI_INSTALL)
    # TODO
endif()

if(NOT GooseUI_HasGraphicService)
    message(FATAL_ERROR "[GooseUI] -- No Graphic Service Detected (Vulkan, OpenGL)")
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "GooseUI" VERSION ${PROJECT_VERSION} SOVERSION "0" FOLDER "GooseUI")