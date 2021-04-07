#pragma once

#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"

#include "IlluminatePacketHandler.h"
#include "IlluminateSocket.h"

using namespace Poco::Net;

class IlluminateServerConnection : public TCPServerConnection
{
public:
	//IlluminateServerConnection() {};
	IlluminateServerConnection(const StreamSocket& socket, IlluminatePacketHandler* packetHandler) : TCPServerConnection(socket), handler(packetHandler) {};
	virtual ~IlluminateServerConnection() {};

	virtual void start() {};
	virtual void run() {};
private:
	IlluminatePacketHandler* handler;
};