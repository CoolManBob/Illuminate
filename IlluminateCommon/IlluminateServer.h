#pragma once

#include "Poco/Net/TCPServer.h"
#include "Poco/Net/ServerSocket.h"

#include "IlluminateConnectionFactory.h"

using namespace Poco::Net;

class IlluminateServer
{
public:
	IlluminateServer() {};
	virtual ~IlluminateServer() {};

	virtual void runServer() {};

private:
	IlluminateConnectionFactory * connectFactory;
};