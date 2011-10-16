include_directories(include)

ADD_EXECUTABLE(tp2 main.cpp lib/MundoTP2.cpp)

add_subdirectory(lib)

TARGET_LINK_LIBRARIES(tp2 framework_lib cuerpos_lib ${CORELIBS})


add_subdirectory(shaders)