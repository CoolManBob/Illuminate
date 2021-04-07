#pragma once

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerParams.h"

using namespace Poco;
using namespace Poco::Net;


#include "IlluminateServer.h"
#include "IlluminateChannelClientFactory.h"
#include "IlluminateChannelPacketHandler.h"

class IlluminateChannelServer : public IlluminateServer
{
public:
	IlluminateChannelServer();
	virtual ~IlluminateChannelServer();

	virtual void runServer();
	void stopServer();

private:
	IlluminateChannelClientFactory * clientFactory;
	TCPServer * channelServer;
	IlluminateChannelPacketHandler * handler;
	TCPServerParams * params;

};