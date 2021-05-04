#pragma once

#include "Poco/Net/StreamSocket.h"

using namespace Poco::Net;

#include "IlluminateSocketImpl.h"
#include "IlluminatePacket.h"
#include "IlluminateBDOCrypt.h"

class IlluminateSocket : public StreamSocket
{
public:
	IlluminateSocket() { cryptoSession = nullptr; };
	IlluminateSocket(const Socket& sock) : StreamSocket(sock) { cryptoSession = nullptr; };
	virtual ~IlluminateSocket() {};

	IlluminateSocket& operator = (const Socket& sock) 
	{ 
		if (dynamic_cast<IlluminateSocketImpl*>(sock.impl()))
			Socket::operator = (sock);
	}

	void setCryptoSession(BDOCrypt* session) { cryptoSession = session; }
	BDOCrypt* getCryptoSession() { return cryptoSession; }
	int sendPacket(IlluminatePacket* packet) 
	{
		if (!cryptoSession)
			return -1;
		
		if (packet->GetCrypted())
			cryptoSession->cryptoProcess(packet->getBufferAt(3), packet->getSize() - 3); //OpCode + body is encrypted
		
		return this->sendBytes(packet->getBuffer(), packet->getSize());
	}
	bool receivePacket(IlluminatePacket * packet) 
	{
		packet->acquirePacketHeader();
		
		if (packet->GetCrypted() && cryptoSession)
			cryptoSession->cryptoProcess(packet->getBuffer(), packet->getSize() - 3);

		packet->acquireOpCode(); //Get the OpCode after crypto is completed

		return true;
	}

private:
	BDOCrypt * cryptoSession;
};