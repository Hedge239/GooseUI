cmake_minimum_required(VERSION 3.10.0)
project(GooseExamples VERSION 0.0.1)

include_directories("../include")
link_libraries(GooseUI OpenGL::GL)

add_executable(EventTest EventTest.cpp)