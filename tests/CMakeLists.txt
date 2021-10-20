CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (tests)

SET (SRC_DIR ${CMAKE_SOURCE_DIR}/src)
SET (INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
SET (SOURCES 
        tests.cpp
        SocketTests.cpp
        ${SRC_DIR}/Socket.cpp
        ${SRC_DIR}/BSDSocketImpl.cpp
        ${SRC_DIR}/BSDSocketEngine.cpp
    )

SET (HEADERS
        ${INCLUDE_DIR}/Socket.h
        ${INCLUDE_DIR}/SocketImpl.h
        ${INCLUDE_DIR}/SocketEngine.h
        ${INCLUDE_DIR}/BSDSocketImpl.h
        ${INCLUDE_DIR}/BSDSocketEngine.h
    )

ADD_EXECUTABLE (tests ${SOURCES})
SET_PROPERTY (TARGET tests PROPERTY CXX_STANDAR 11)
TARGET_LINK_LIBRARIES (tests gtest)
TARGET_INCLUDE_DIRECTORIES (tests PRIVATE ${INCLUDE_DIR})

ADD_CUSTOM_TARGET (JUnitTestReport
    COMMAND $<TARGET_FILE:tests> --gtest_output="xml:$ENV{BINARY_DIR}/tests.xml"
    DEPENDS tests
)

IF (WIN32)
    TARGET_LINK_LIBRARIES (tests ws2_32)
ENDIF ()
