#if defined(__linux__) || defined(__APPLE_CC__)
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#endif

#include "smartftpd/BSDSocketImpl.h"

BSDSocketImpl::BSDSocketImpl()
{
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd <= 0) {
        //TODO: exception
    }
}

BSDSocketImpl::BSDSocketImpl(int sockfd)
    : sockfd(sockfd)
{
    if (this->sockfd <= 0) {
        //TODO: exception
    }
}

BSDSocketImpl::~BSDSocketImpl()
{
    close();
}

bool
BSDSocketImpl::bind(const struct sockaddr_in& addr)
{
    return ::bind(this->sockfd, (struct sockaddr *)&addr, sizeof(addr)) == 0;
}

bool
BSDSocketImpl::reuse()
{
    int enable = 1;
    return setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&enable, sizeof(enable)) == 0;
}

int
BSDSocketImpl::listen(int backlog)
{
    return ::listen(this->sockfd, backlog);
}

SocketImplHolder
BSDSocketImpl::accept()
{
    int sockfd = ::accept(this->sockfd, 0, 0);
    if (sockfd > 0) {
        return std::make_unique<BSDSocketImpl>(sockfd);
    }

    return {};
}

void
BSDSocketImpl::close()
{
    if (this->sockfd > 0) {
#if defined(__linux__) || defined(__APPLE_CC__)
        ::close(this->sockfd);
#elif defined(_WIN32) || defined(_WIN64)
        closesocket(this->sockfd);
#endif
    }
}
