#include <sys/types.h>
#include <sys/socket.h>
#include <stdexcept>
#include <string.h>
#include <errno.h>
#include "smartftpd/Socket.h"
#include "smartftpd/SocketImpl.h"

Socket::Socket()
    : impl(0)
{
    setImpl();
}

void
Socket::bind(uint16_t port)
{
    struct sockaddr_in addr = {0};
    addr.sin_len = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (!getImpl().bind(addr)) {
        throw std::runtime_error(strerror(errno));
    }
}

SocketImpl&
Socket::getImpl() const
{
    return *this->impl;
}

void
Socket::setImpl()
{
    this->impl = new SocketImpl();
}
