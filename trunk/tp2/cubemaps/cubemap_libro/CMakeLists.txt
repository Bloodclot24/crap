file(GLOB textura RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.png")
foreach(file ${textura})
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${file} ${CMAKE_CURRENT_BINARY_DIR}/${file} COPYONLY)  
endforeach()
       