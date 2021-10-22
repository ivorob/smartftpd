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

namespace {

class MockSocketImpl : public SocketImpl {
public:
    bool bind(const struct sockaddr_in& addr) override {
        std::lock_guard<std::mutex> lock(mockImplMutex);

        this->ports.insert(htons(addr.sin_port));
        return true;
    }

    bool reuse() override {
        return true;
    }

    bool connect(const std::string& hostname, uint16_t port) override {
        std::lock_guard<std::mutex> lock(mockImplMutex);

        if (this->ports.count(port) == 0) {
            return false;
        }

        this->ports.insert(port);
        return true;
    }

    int listen(int backlog) override {
        return 0;
    }

    void close() override {
    }

    SocketImplHolder accept() override {
        return std::make_unique<MockSocketImpl>();
    }
private:
    static std::set<uint16_t> ports;
    static std::mutex mockImplMutex;
};

std::set<uint16_t> MockSocketImpl::ports;
std::mutex MockSocketImpl::mockImplMutex;

class MockSocketEngine : public SocketEngine {
public:
    SocketImplHolder makeImpl() override {
        return std::make_unique<MockSocketImpl>();
    }

    SocketImplHolder makeImpl(int sockfd) override {
        return {};
    }
};

void connectToPort(uint16_t port) {
    MockSocketEngine socketEngine;
    Socket socket(socketEngine);
    if (!socket.connect("localhost", port)) {
        FAIL() << "Connection failed to port " << port;
    }
}

}

TEST(SocketTests, Bind)
{
    MockSocketEngine socketEngine;
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
    MockSocketEngine socketEngine;
    Socket tcpSocket(socketEngine);
    tcpSocket.bind(10021);

    std::thread thread(connectToPort, 10021);
    Socket newSocket = tcpSocket.accept();
    if (thread.joinable()) {
        thread.join();
    }
}

TEST(SocketTests, connecting_to_invalid_port_is_failed)
{
    MockSocketEngine socketEngine;

    Socket socket(socketEngine);

    ASSERT_FALSE(socket.connect("localhost", 10022));
}
