#ifndef __SMARTFTPD_SOCKET_H__
#define __SMARTFTPD_SOCKET_H__

#include <cstdint>

class SocketImpl;

class Socket {
public:
    Socket();

    void bind(uint16_t port);
private:
    SocketImpl& getImpl() const;
    void setImpl();
private:
    SocketImpl *impl;
};

#endif //__SMARTFTPD_SOCKET_H__
