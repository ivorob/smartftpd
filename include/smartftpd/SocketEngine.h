#pragma once

#include "smartftpd/SocketImpl.h"

class SocketEngine {
public:
    virtual ~SocketEngine() = default;

    virtual SocketImplHolder makeImpl() = 0;
    virtual SocketImplHolder makeImpl(int sockfd) = 0;
};
