cmake_minimum_required(VERSION 2.4)
PROJECT(CRAP)

SET(CMAKE_BUILD_TYPE debug)
SET(CMAKE_CXX_FLAGS "-Wall -ggdb -rdynamic")

find_package(OpenGL)
find_package(GLUT)

set(CORELIBS ${OPENGL_LIBRARY} -lglut GLEW)

add_subdirectory(tp1)
add_subdirectory(tp2)
add_subdirectory(tp3)
add_Subdirectory(solar)
add_Subdirectory(GLDEMO)
add_Subdirectory(bullet-demo)


 