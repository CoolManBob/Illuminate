#pragma once

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerParams.h"

using namespace Poco;
using namespace Poco::Net;

#define UPDATETIMEFACTOR 1000000 //1 second
#define UPDATETIMESECONDS 60 //60 seconds
#define UPDATETIMER UPDATETIMESECONDS*UPDATETIMEFACTOR

#include "IlluminateServer.h"
#include "IlluminateLoginClientFactory.h"
#include "IlluminateLoginPacketHandler.h"

class IlluminateLoginServer : public IlluminateServer
{
public:
	IlluminateLoginServer();
	virtual ~IlluminateLoginServer();

	virtual void runServer();
	void stopServer();
	void updateServer();

private:
	void initDatabase();
	bool initServerSystems();

	Timestamp timeStamp;
	IlluminateLoginClientFactory * clientFactory;
	TCPServer * loginServer;
	IlluminateLoginPacketHandler * handler;
	TCPServerParams * params;

};