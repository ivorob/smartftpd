CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
PROJECT (smartftpd)

SET (SRC_DIR src)
SET (SOURCES 
        ${SRC_DIR}/main.cpp)

OPTION (BUILD_TESTING "Build testing" OFF)

SET (CMAKE_CXX_STANDARD 17)

ADD_SUBDIRECTORY (thirdparty)

IF (BUILD_TESTING)
    ENABLE_TESTING ()
    ADD_SUBDIRECTORY (tests tests)

    ADD_TEST (tests tests/tests)
ENDIF ()

ADD_EXECUTABLE (smartftpd ${SOURCES})
