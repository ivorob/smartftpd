#pragma once

#include <memory>

#include "smartftpd/SocketImpl.h"

class BSDSocketImpl : public SocketImpl {
public:
    BSDSocketImpl();
    BSDSocketImpl(int sockfd);
    virtual ~BSDSocketImpl();

    bool bind(const struct sockaddr_in& addr) override;
    bool reuse() override;

    int listen(int backlog) override;
    void close() override;

    SocketImplHolder accept() override;
private:
    int sockfd = -1;
};
