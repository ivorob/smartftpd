#include <thread>
#include <gtest/gtest.h>

#if defined(__linux__)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#endif

#include "smartftpd/Socket.h"

namespace {

void connectToPort(uint16_t port) {
    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd > 0) {
        struct sockaddr_in addr;
#if defined(__linux__)
        addr.sin_len = sizeof(addr);
#endif 
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        if (connect(sockfd, (const struct sockaddr *)&addr, sizeof(addr)) < 0) {
            FAIL() << "Connection failed to port " << port;
        }
    }
}

}

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

TEST(SocketTests, Accept)
{
    Socket tcpSocket;
    tcpSocket.bind(10021);

    std::thread thread(connectToPort, 10021);
    Socket newSocket = tcpSocket.accept();
    thread.join();
}
