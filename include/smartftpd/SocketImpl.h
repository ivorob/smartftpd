#pragma once

#include <memory>
#include <string>

#if defined(__linux__) || defined(__APPLE_CC__)
#include <netinet/in.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#endif

class SocketImpl;

using SocketImplHolder = std::unique_ptr<SocketImpl>;

class SocketImpl {
public:
    SocketImpl() = default;
    SocketImpl(const SocketImpl&) = delete;
    SocketImpl(SocketImpl&&) = delete;
    virtual ~SocketImpl() = default;

    SocketImpl& operator=(const SocketImpl&) = delete;
    SocketImpl& operator=(SocketImpl&&) = delete;

    virtual bool bind(const struct sockaddr_in& addr) = 0;
    virtual bool reuse() = 0;
    virtual bool connect(const std::string& hostname, uint16_t port) = 0;

    virtual int listen(int backlog) = 0;
    virtual void close() = 0;

    virtual SocketImplHolder accept() = 0;
};
