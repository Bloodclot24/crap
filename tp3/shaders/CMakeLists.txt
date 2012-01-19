file(GLOB fragment RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.frag")
file(GLOB vertex RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.vert")
foreach(file ${fragment} ${vertex})
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${file} ${CMAKE_CURRENT_BINARY_DIR}/${file} COPYONLY)  
endforeach()
       