#pragma once
#include <iostream>
using std::cout;
using std::endl;

#include "IlluminateConnectionFactory.h"
#include "IlluminateWorldPacketHandler.h"
#include "IlluminateWorldClientConnection.h"
#include "IlluminateSocket.h"

class IlluminateWorldClientFactory : public IlluminateConnectionFactory
{
public:
	IlluminateWorldClientFactory(IlluminateWorldPacketHandler* handler) : packetHandler(handler) {};
	virtual ~IlluminateWorldClientFactory() {};

	virtual IlluminateWorldClientConnection* createConnection(const StreamSocket& socket)
	{
		cout << "New connection recieved, spawning IlluminateWorldClientConnection" << endl;
		return new IlluminateWorldClientConnection(socket, packetHandler);
	}

private:
	IlluminateWorldPacketHandler * packetHandler;
};