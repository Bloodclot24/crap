cmake_minimum_required(VERSION 2.4)
PROJECT(CRAP)

SET(CMAKE_BUILD_TYPE debug)
SET(CMAKE_CXX_FLAGS "-Wall -ggdb")

find_package(OpenGL)
find_package(GLUT)

set(CORELIBS ${OPENGL_LIBRARY} ${GLUT_LIBRARY})

add_subdirectory(tp1)
add_Subdirectory(solar)

