#ifndef __SMARTFTPD_SOCKET_IMPL_H__
#define __SMARTFTPD_SOCKET_IMPL_H__

#include <netinet/in.h>

class SocketImpl {
public:
    SocketImpl();
    SocketImpl(int sockfd);
    SocketImpl(const SocketImpl& impl);
    virtual ~SocketImpl();

    bool bind(const struct sockaddr_in& addr);
    bool reuse();

    int listen(int backlog);
    void close();

    SocketImpl *accept();
private:
    int sockfd;
};

#endif //__SMARTFTPD_SOCKET_IMPL_H__
