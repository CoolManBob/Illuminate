#pragma once

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerParams.h"

using namespace Poco;
using namespace Poco::Net;


#include "IlluminateServer.h"
#include "IlluminateWorldClientFactory.h"
#include "IlluminateWorldPacketHandler.h"

class IlluminateWorldServer : public IlluminateServer
{
public:
	IlluminateWorldServer();
	virtual ~IlluminateWorldServer();

	virtual void runServer();
	void stopServer();

private:
	IlluminateWorldClientFactory * clientFactory;
	TCPServer * worldServer;
	IlluminateWorldPacketHandler * handler;
	TCPServerParams * params;

};