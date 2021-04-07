#pragma once
#include <iostream>
using std::cout;
using std::endl;

#include "IlluminateConnectionFactory.h"
#include "IlluminateChannelPacketHandler.h"
#include "IlluminateChannelClientConnection.h"
#include "IlluminateSocket.h"

class IlluminateChannelClientFactory : public IlluminateConnectionFactory
{
public:
	IlluminateChannelClientFactory(IlluminateChannelPacketHandler* handler) : packetHandler(handler) {};
	virtual ~IlluminateChannelClientFactory() {};

	virtual IlluminateChannelClientConnection* createConnection(const StreamSocket& socket)
	{
		cout << "New connection recieved, spawning IlluminateChannelClientConnection" << endl;
		return new IlluminateChannelClientConnection(socket, packetHandler);
	}

private:
	IlluminateChannelPacketHandler * packetHandler;
};