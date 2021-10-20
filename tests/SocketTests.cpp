#include <thread>
#include <gtest/gtest.h>

#if defined(__linux__) || defined(__APPLE_CC__)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#endif

#include "smartftpd/Socket.h"
#include "smartftpd/BSDSocketEngine.h"

namespace {

void connectToPort(uint16_t port) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd > 0) {
        struct sockaddr_in addr;
#if defined(__APPLE_CC__) 
        addr.sin_len = sizeof(addr);
#endif 
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);

        struct hostent *host = gethostbyname("localhost");
        memcpy(&addr.sin_addr.s_addr, host->h_addr_list[0], sizeof(addr.sin_addr.s_addr));
        if (connect(sockfd, (const struct sockaddr *)&addr, sizeof(addr)) < 0) {
            FAIL() << "Connection failed to port " << port;
        }

#if defined(__linux__) || defined(__APPLE_CC__)
        ::close(sockfd);
#elif defined(_WIN32) || defined(_WIN64)
        closesocket(sockfd);
#endif 
    }
}

}

TEST(SocketTests, Bind)
{
    BSDSocketEngine socketEngine;
    Socket tcpSocket(socketEngine);
#if defined(__linux__)
    try {
        tcpSocket.bind(21);
        FAIL() << "Permission denied exception expected";
    } catch (const std::exception& error) {
        ASSERT_STREQ("Permission denied", error.what());
    }
#endif

    try {
        tcpSocket.bind(10021);
    } catch (const std::exception& error) {
        FAIL() << "No exception expected: " << error.what();
    }
}

TEST(SocketTests, Accept)
{
    BSDSocketEngine socketEngine;
    Socket tcpSocket(socketEngine);
    tcpSocket.bind(10021);

    std::thread thread(connectToPort, 10021);
    Socket newSocket = tcpSocket.accept();
    thread.join();
}
