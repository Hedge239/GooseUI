cmake_minimum_required(VERSION 3.5.0)
project(ZephyrUI VERSION 0.0.1)

option(ZEPHYR_BUILD_TESTS "Builds included examples/test projects" ON)
option(ZEPHYR_X11_SUPPORT "Includes both X11 and Wayland support" ON)

include(".buildtools/Cmake/Zephyr.cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/.buildtools/Cmake/modules")

if(WIN32)
    message(STATUS "Operating System: Win32")
    message(STATUS "Display Server: Win32")

    include(".buildtools/cmake/platforms/win32.cmake")
elseif(UNIX)
    message(STATUS "Operating System: UNIX")

    if(ZEPHYR_X11_SUPPORT)
        message(STATUS "Display Server: X11/WAYLAND HYBRID")

        include(".buildtools/Cmake/platforms/wayland.cmake")
        include(".buildtools/Cmake/platforms/xorg.cmake")

        find_package(X11 REQUIRED)
        find_package(Wayland REQUIRED)

        list(APPEND ZEPHYR_DEP_INCLUDE "${X11_X11_INCLUDE_PATH}")
        list(APPEND ZEPHYR_DEP_INCLUDE "${WAYLAND_INCLUDE_DIRS}")

        list(APPEND ZPEHYR_DEP_LIB "${X11_X11_LIB}")
        list(APPEND ZEPHYR_DEP_SRC "${WAYLAND_LIBRARIES}")

        list(APPEND BUILD_FLAGS "wayland-client")
        list(APPEND BUILD_FLAGS "X11")

        add_compile_definitions(X11_SUPPORT)
    else()
        message(STATUS "Display Server: WAYLAND")

        include(".buildtools/Cmake/platforms/wayland.cmake")

        find_package(Wayland REQUIRED)

        list(APPEND ZEPHYR_DEP_INCLUDE "${WAYLAND_INCLUDE_DIRS}")
        list(APPEND ZEPHYR_DEP_SRC "${WAYLAND_LIBRARIES}")

        list(APPEND BUILD_FLAGS "wayland-client")
    endif()
else()
    message(FATAL_ERROR "Faild to find valid display service")
endif()

set(ZEPHYR_SRC ${ZEPHYR_LIB_SRC} ${ZEPHYR_PLATFORM_SRC})

add_library(ZephyrUI ${ZEPHYR_SRC} "include")
set_target_properties(ZephyrUI PROPERTIES OUTPUT_NAME "ZephyrUI" VERSION ${PROJECT_VERSION} SOVERSION "0" FOLDER "ZephyrUI")

target_include_directories(ZephyrUI PRIVATE "include" ${ZEPHYR_DEP_INCLUDE})
target_link_directories(ZephyrUI PRIVATE ${ZEPHYR_DEP_SRC} ${BUILD_FLAGS})

if(ZEPHYR_BUILD_TESTS)
    add_subdirectory(tests)
endif()