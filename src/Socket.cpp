#if defined(__linux__)
#include <sys/types.h>
#include <sys/socket.h>
#endif

#include <stdexcept>
#include <string.h>
#include <errno.h>
#include "smartftpd/Socket.h"
#include "smartftpd/SocketImpl.h"

Socket::Socket(SocketEngine& engine)
    : impl(engine.makeImpl())
{
}

Socket::Socket(SocketImplHolder impl)
    : impl(std::move(impl))
{
}

void
Socket::bind(uint16_t port)
{
    getImpl().reuse();

    struct sockaddr_in addr = {0};
#if defined(__APPLE_CC__)
    addr.sin_len = sizeof(addr);
#endif
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (!getImpl().bind(addr)) {
        throw std::runtime_error(strerror(errno));
    }
}

bool
Socket::connect(const std::string& hostname, uint16_t port)
{
    return getImpl().connect(hostname, port);
}

SocketImpl&
Socket::getImpl() const
{
    return *this->impl;
}

void
Socket::setImpl(SocketImplHolder newImpl)
{
    this->impl = std::move(newImpl);
}

Socket
Socket::accept()
{
    getImpl().listen(SOMAXCONN);
    return Socket(getImpl().accept());
}
