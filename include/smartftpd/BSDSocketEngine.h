#pragma once

#include "smartftpd/SocketEngine.h"

class BSDSocketEngine : public SocketEngine {
public:
    SocketImplHolder makeImpl() override;
    SocketImplHolder makeImpl(int sockfd) override;
};
