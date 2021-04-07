#pragma once

#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/StreamSocket.h"

#include "IlluminatePacketHandler.h"
#include "IlluminateServerConnection.h"
#include "IlluminateSocket.h"

using namespace Poco::Net;

class IlluminateConnectionFactory : public TCPServerConnectionFactory
{
public:
	IlluminateConnectionFactory() {};
	IlluminateConnectionFactory(IlluminatePacketHandler* packetHandler) : handler(packetHandler) {};
	virtual ~IlluminateConnectionFactory() {};

	virtual IlluminateServerConnection* createConnection(const StreamSocket& socket) { return new IlluminateServerConnection(socket, handler); };

private:
	IlluminatePacketHandler* handler;
};