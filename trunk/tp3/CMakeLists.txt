include_directories(include)
include_directories("/usr/include/bullet")

set(BULLET_LIBS -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath)

add_subdirectory(lib)

ADD_EXECUTABLE(tp3 main.cpp lib/TP3.cpp)

TARGET_LINK_LIBRARIES(tp3 framework_final_lib ${CORELIBS} ${BULLET_LIBS})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lad.raw ${CMAKE_CURRENT_BINARY_DIR}/lad.raw COPYONLY)

file(GLOB texturas RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.raw")
foreach(file ${texturas})
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${file} ${CMAKE_CURRENT_BINARY_DIR}/${file} COPYONLY)  
endforeach()

add_subdirectory(shaders)
