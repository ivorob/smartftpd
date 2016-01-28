CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (tests)

SET (SRC_DIR ../src)
SET (SOURCES 
        tests.cpp
        SocketTests.cpp
        ${SRC_DIR}/Socket.cpp
        ${SRC_DIR}/SocketImpl.cpp)

INCLUDE_DIRECTORIES (. ../include/)

ADD_EXECUTABLE (tests ${SOURCES})
TARGET_LINK_LIBRARIES (tests gtest)
