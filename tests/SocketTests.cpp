#include <gtest/gtest.h>
#include "smartftpd/Socket.h"

TEST(SocketTests, Bind)
{
    Socket tcpSocket;
    try {
        tcpSocket.bind(21);
        FAIL() << "Permission denied exception expected";
    } catch (const std::exception& error) {
        ASSERT_STREQ("Permission denied", error.what());
    }

    try {
        tcpSocket.bind(10021);
    } catch (...) {
        FAIL() << "No exception expected";
    }
}
