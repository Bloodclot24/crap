include_directories("/usr/include/bullet")
set(BULLET_LIBS -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath)

ADD_EXECUTABLE(demo1 BulletHelloWorld.cpp)
TARGET_LINK_LIBRARIES(demo1 ${CORELIBS} ${BULLET_LIBS})

ADD_EXECUTABLE(demo2 BulletHolaMundo.cpp)
TARGET_LINK_LIBRARIES(demo2 ${CORELIBS} ${BULLET_LIBS})

