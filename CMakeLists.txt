cmake_minimum_required(VERSION 2.4)
PROJECT(CRAP)

SET(CMAKE_BUILD_TYPE debug)
SET(CMAKE_CXX_FLAGS "-Wall -ggdb")

ADD_EXECUTABLE(framework main.cpp)
TARGET_LINK_LIBRARIES(framework -lGL -lGLU -lglut)
