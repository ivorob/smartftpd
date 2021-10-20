#include "smartftpd/BSDSocketEngine.h"
#include "smartftpd/BSDSocketImpl.h"

SocketImplHolder
BSDSocketEngine::makeImpl()
{
    return std::make_unique<BSDSocketImpl>();
}

SocketImplHolder
BSDSocketEngine::makeImpl(int sockfd)
{
    return std::make_unique<BSDSocketImpl>(sockfd);
}
