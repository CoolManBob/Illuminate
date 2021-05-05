#pragma once
#pragma once

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMLoginUserToAuthenticServer : public IlluminatePacketProcessor
{
public:
	CMLoginUserToAuthenticServer() {};
	virtual ~CMLoginUserToAuthenticServer() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
