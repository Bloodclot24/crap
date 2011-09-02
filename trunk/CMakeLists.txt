cmake_minimum_required(VERSION 2.4)
PROJECT(CRAP)

SET(INCLUDES ${CRAP_SOURCE_DIR}/include)

SET(CMAKE_BUILD_TYPE debug)
SET(CMAKE_CXX_FLAGS "-Wall -I${INCLUDES} -ggdb")

ADD_EXECUTABLE(framework main.cpp)
TARGET_LINK_LIBRARIES(framework -lGL -lGLU -lglut)

ADD_EXECUTABLE(solar solar_system_main.cpp)
TARGET_LINK_LIBRARIES(solar -lGL -lGLU -lglut)
