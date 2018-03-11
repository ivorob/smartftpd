CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (tests)

SET (SRC_DIR ../src)
SET (SOURCES 
        tests.cpp
        SocketTests.cpp
        ${SRC_DIR}/Socket.cpp
        ${SRC_DIR}/SocketImpl.cpp)

INCLUDE_DIRECTORIES (. ../include/)

ADD_SUBDIRECTORY (
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdparty/googletest
    ${CMAKE_BINARY_DIR}/googletest)

ADD_EXECUTABLE (tests ${SOURCES})
SET_PROPERTY (TARGET tests PROPERTY CXX_STANDAR 11)
TARGET_LINK_LIBRARIES (tests gtest)

IF (WIN32)
    TARGET_LINK_LIBRARIES (tests ws2_32)
ENDIF ()
