#ifndef __SMARTFTPD_SOCKET_IMPL_H__
#define __SMARTFTPD_SOCKET_IMPL_H__

#include <netinet/in.h>

class SocketImpl {
public:
    SocketImpl();

    bool bind(const struct sockaddr_in& addr);
private:
    int sockfd;
};

#endif //__SMARTFTPD_SOCKET_IMPL_H__
