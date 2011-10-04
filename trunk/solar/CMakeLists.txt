ADD_EXECUTABLE(solar solar_system_main.cpp)
TARGET_LINK_LIBRARIES(solar ${CORELIBS})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/earth.raw ${CMAKE_CURRENT_BINARY_DIR}/earth.raw COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sunmap.raw ${CMAKE_CURRENT_BINARY_DIR}/sunmap.raw COPYONLY)