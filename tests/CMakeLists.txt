CMAKE_MINIMUM_REQUIRED(VERSION 4.2.0)
PROJECT(GooseUI-tests VERSION 0.0.1)

link_libraries(GooseUI OpenGL::GL)

add_executable(WindowTest windowTest.cpp)