include_directories(include)
include_directories("/usr/include/bullet")

set(BULLET_LIBS -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath)

add_subdirectory(lib)

ADD_EXECUTABLE(tp3 main.cpp lib/TP3.cpp)

TARGET_LINK_LIBRARIES(tp3 framework_final_lib ${CORELIBS} ${BULLET_LIBS} -lIL)

add_subdirectory(shaders)
