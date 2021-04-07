#pragma once

#include "Poco/Net/StreamSocket.h"
using Poco::Net::StreamSocket;

#include "IlluminateLoginGlobal.h"
#include "IlluminatePacketProcessor.h"
#include "IlluminateSocket.h"

class IlluminateLoginServerList : public IlluminatePacketProcessor
{
public:
	IlluminateLoginServerList() {};
	virtual ~IlluminateLoginServerList() {};

	virtual bool processPacket(const localInfo& local);
	bool processServerList(localInfo& local);
	bool processServerExtra(localInfo& local);

	enum SERVERLISTOPERATION
	{
		SERVERLIST_REQ = 0,
		SERVERLIST_ANS = 2,
	};
};