#ifndef __SMARTFTPD_SOCKET_H__
#define __SMARTFTPD_SOCKET_H__

#include <cstdint>

class SocketImpl;

class Socket {
public:
    Socket();
    Socket(Socket&& other);
    virtual ~Socket();

    void bind(uint16_t port);
    Socket accept();
protected:
    virtual void setImpl(SocketImpl *impl = 0);
private:
    SocketImpl& getImpl() const;
    void clearImpl();
private:
    SocketImpl *impl;
};

#endif //__SMARTFTPD_SOCKET_H__
