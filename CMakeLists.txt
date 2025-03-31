cmake_minimum_required(VERSION 3.10.0)
project(ZephyrUI VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/build_systems/cmake/modules")

include("${CMAKE_SOURCE_DIR}/build_systems/cmake/core.cmake")
include("${CMAKE_SOURCE_DIR}/build_systems/cmake/widgets.cmake")

# BUILD OPTIONS | Non-functional if commited out #

    option(zSUPPORT_WAYLAND "Includes Wayland Support" ON)
    option(zSUPPORT_X11 "Includes X11 Support" ON)
    option(zSUPPORT_WINAPI "Includes Win32API Support" ON)
    #option(ZSUPPORT_APPLE "Includes what ever apple uses" OFF)

    #option(zSUPPORT_OPENGL "Includes inbedding OpenGL" OFF)
    #option(zSUPPORT_VULKAN "Includes Inbedding Vulkan" OFF)

    option(zBUILD_TESTS "Builds included examples & test applications" ON)

# END BUILD OPTIONS #

# Display Services
if(WIN32)
    message(STATUS "Detected OS: Windows")

    if(zSUPPORT_WINAPI)
        message(STATUS "Display Service: Win32API")
        set(hasDisplayService true)

        include("${CMAKE_SOURCE_DIR}/build_systems/cmake/platform/win32api.cmake")
        add_compile_definitions(zUseWin32API)
    endif()

endif()

if(UNIX AND NOT APPLE)
    message(STATUS "Detected OS: UNIX Based")

    if(zSUPPORT_X11)
        message(STATUS "Display Service Enabled: X11")
        set(hasDisplayService true)

        find_package(X11 REQUIRED)

        list(APPEND zLIB_INCLUDE "${X11_X11_INCLUDE_PATH}")
        list(APPEND zLIB_LIB "${X11_X11_LIB}")
        list(APPEND zLIB_FLAGS "X11")

        include("${CMAKE_SOURCE_DIR}/build_systems/cmake/platform/x11.cmake")
        add_compile_definitions(zUseX11)
    endif()

    if(zSUPPORT_WAYLAND)
        message(STATUS "Display Service Enabled: Wayland")
        set(hasDisplayService true)

        find_package(Wayland REQUIRED)

        list(APPEND zLIB_INCLUDE "${WAYLAND_CLIENT_INCLUDE_PATH}")
        list(APPEND zLIB_LIB "${WAYLAND_CLIENT_LIB}")
        list(APPEND zLIB_FLAGS "wayland-client")

        include("${CMAKE_SOURCE_DIR}/build_systems/cmake/platform/wayland.cmake")
        add_compile_definitions(zUseWayland)
    endif()

endif()

if(APPLE)
    message(STATUS "Detected OS: Apple")
    message(FATAL_ERROR "Display Service: Unknown - Not Supported")
endif()

if(NOT hasDisplayService)
    message(FATAL_ERROR "Fatal Error: Faild to find display service")
endif()


# Lib
set(zLIB_SRC ${zCORE} ${zWIDGETS} ${zPLATFORM})
add_library(${PROJECT_NAME} ${zLIB_SRC} "include")

target_include_directories(${PROJECT_NAME} PRIVATE "include" ${zLIB_INCLUDE})
target_link_directories(${PROJECT_NAME} PRIVATE ${zLIB_LIB} ${zLIB_FLAGS})

if(zBUILD_TESTS)
    add_subdirectory(tests)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "ZephyrUI" VERSION ${PROJECT_VERSION} SOVERSION "0" FOLDER "ZephyrUI")