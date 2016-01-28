#include <sys/types.h>
#include <sys/socket.h>
#include "smartftpd/SocketImpl.h"

SocketImpl::SocketImpl()
{
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd <= 0) {
        //TODO: exception
    }
}

bool
SocketImpl::bind(const struct sockaddr_in& addr)
{
    return ::bind(this->sockfd, (struct sockaddr *)&addr, sizeof(addr)) == 0;
}
