include_directories(include)

ADD_EXECUTABLE(tp2 main.cpp lib/MundoTP2.cpp)

add_subdirectory(lib)

TARGET_LINK_LIBRARIES(tp2 framework_lib cuerpos_lib ${CORELIBS})

file(GLOB fragment RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.raw")
foreach(file ${fragment} ${vertex})
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${file} ${CMAKE_CURRENT_BINARY_DIR}/${file} COPYONLY)  
endforeach()


add_subdirectory(shaders)