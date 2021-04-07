#pragma once
#include <iostream>
using std::cout;
using std::endl;

#include "IlluminateConnectionFactory.h"
#include "IlluminateLoginPacketHandler.h"
#include "IlluminateLoginClientConnection.h"
#include "IlluminateSocket.h"

class IlluminateLoginClientFactory : public IlluminateConnectionFactory
{
public:
	IlluminateLoginClientFactory(IlluminateLoginPacketHandler* handler) : packetHandler(handler) {};
	virtual ~IlluminateLoginClientFactory() {};

	virtual IlluminateLoginClientConnection* createConnection(const StreamSocket& socket) 
	{ 
		LOG("New connection recieved, spawning IlluminateLoginClientConnection");
		return new IlluminateLoginClientConnection(socket, packetHandler);
	}

private:
	IlluminateLoginPacketHandler * packetHandler;
};