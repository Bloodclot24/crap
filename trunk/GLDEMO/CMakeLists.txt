include_directories(include cwc/include)
add_executable(gldemo main.cpp src/myApplication.cpp src/myWindow.cpp cwc/source/glApplication.cpp cwc/source/glWindow.cpp cwc/source/glutwindow.cpp)

TARGET_LINK_LIBRARIES(gldemo ${CORELIBS} GLEW)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/BasicFShader.frag ${CMAKE_CURRENT_BINARY_DIR}/BasicFShader.frag COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/PassThroughVShader.vert ${CMAKE_CURRENT_BINARY_DIR}/PassThroughVShader.vert COPYONLY)
