include_directories(include)

ADD_EXECUTABLE(tp2 main.cpp)

add_subdirectory(lib)

TARGET_LINK_LIBRARIES(tp2 framework_lib ${CORELIBS})

