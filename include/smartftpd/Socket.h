#pragma once

#include <cstdint>

#include "SocketImpl.h"
#include "SocketEngine.h"

class Socket {
public:
    Socket(SocketEngine& engine);
    Socket(SocketImplHolder impl);
    Socket(Socket&& other) = default;
    virtual ~Socket() = default;

    void bind(uint16_t port);
    bool connect(const std::string& hostname, uint16_t port);
    Socket accept();
protected:
    virtual void setImpl(SocketImplHolder impl);
private:
    SocketImpl& getImpl() const;
private:
    std::unique_ptr<SocketImpl> impl;
};
