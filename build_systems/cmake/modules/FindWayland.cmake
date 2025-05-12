# Find wayland-client files
find_path(WAYLAND_CLIENT_INCLUDE_PATH NAMES wayland-client.h PATHS /usr/include /usr/local/include)
find_library(WAYLAND_CLIENT_LIB NAMES wayland-client PATHS /usr/lib /usr/local/lib)

mark_as_advanced(WAYLAND_CLIENT_INCLUDE_PATH WAYLAND_CLIENT_LIB)