include_directories(include)

ADD_EXECUTABLE(tp2 main.cpp lib/MundoTP2.cpp)

add_subdirectory(lib)

TARGET_LINK_LIBRARIES(tp2 framework_lib cuerpos_lib ${CORELIBS} -lIL)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lad.raw ${CMAKE_CURRENT_BINARY_DIR}/lad.raw COPYONLY)

file(GLOB texturas RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.raw")
foreach(file ${texturas})
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${file} ${CMAKE_CURRENT_BINARY_DIR}/${file} COPYONLY)  
endforeach()


add_subdirectory(cubemaps) 
add_subdirectory(shaders)
