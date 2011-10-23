include_directories(include)

ADD_EXECUTABLE(tp2 main.cpp lib/MundoTP2.cpp)

add_subdirectory(lib)

TARGET_LINK_LIBRARIES(tp2 framework_lib cuerpos_lib ${CORELIBS})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/grilla.raw ${CMAKE_CURRENT_BINARY_DIR}/grilla.raw COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/earth.raw ${CMAKE_CURRENT_BINARY_DIR}/earth.raw COPYONLY)
add_subdirectory(shaders)