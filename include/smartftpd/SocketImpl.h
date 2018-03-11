#pragma once

#if defined(__linux__)
#include <netinet/in.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#endif

class SocketImpl {
public:
#if defined(__linux__)
    typedef int SOCKET;
#endif
    SocketImpl();
    SocketImpl(SOCKET sockfd);
    SocketImpl(const SocketImpl& impl);
    virtual ~SocketImpl();

    bool bind(const struct sockaddr_in& addr);
    bool reuse();

    int listen(int backlog);
    void close();

    SocketImpl *accept();
private:
    SOCKET sockfd;
};
