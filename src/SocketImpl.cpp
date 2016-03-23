#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "smartftpd/SocketImpl.h"

SocketImpl::SocketImpl()
{
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd <= 0) {
        //TODO: exception
    }
}

SocketImpl::SocketImpl(int sockfd)
    : sockfd(sockfd)
{
    if (this->sockfd <= 0) {
        //TODO: exception
    }
}

SocketImpl::SocketImpl(const SocketImpl& impl)
    : sockfd(impl.sockfd)
{
    if (this->sockfd <= 0) {
        //TODO: exception
    }
}

SocketImpl::~SocketImpl()
{
}

bool
SocketImpl::bind(const struct sockaddr_in& addr)
{
    return ::bind(this->sockfd, (struct sockaddr *)&addr, sizeof(addr)) == 0;
}

bool
SocketImpl::reuse()
{
    int enable = 1;
    return setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0;
}

int
SocketImpl::listen(int backlog)
{
    return ::listen(this->sockfd, backlog);
}

SocketImpl *
SocketImpl::accept()
{
    int sockfd = ::accept(this->sockfd, 0, 0);
    return sockfd > 0 ? new SocketImpl(sockfd) : 0;
}

void
SocketImpl::close()
{
    if (this->sockfd > 0) {
        ::close(this->sockfd);
    }
}
