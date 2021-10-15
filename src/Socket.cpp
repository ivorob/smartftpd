#if defined(__linux__)
#include <sys/types.h>
#include <sys/socket.h>
#endif

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

Socket::Socket(Socket&& other)
    : impl(0)
{
    setImpl(new SocketImpl(other.getImpl()));
    other.clearImpl();
}

Socket::~Socket()
{
    if (this->impl) {
        getImpl().close();
    }
    clearImpl();
}

void
Socket::bind(uint16_t port)
{
    getImpl().reuse();

    struct sockaddr_in addr = {0};
#if !defined(__linux__)
    addr.sin_len = sizeof(addr);
#endif
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
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
Socket::setImpl(SocketImpl *impl)
{
    if (this->impl) {
        getImpl().close();
        clearImpl();
    }

    if (!impl) {
        this->impl = new SocketImpl();
    } else {
        this->impl = impl;
    }
}

void
Socket::clearImpl()
{
    delete this->impl;
    this->impl = 0;
}

Socket
Socket::accept()
{
    getImpl().listen(SOMAXCONN);
    Socket newSocket;
    newSocket.setImpl(getImpl().accept());
    return std::move(newSocket);
}
