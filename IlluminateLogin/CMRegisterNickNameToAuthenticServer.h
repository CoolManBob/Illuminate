#pragma once

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMRegisterNickNameToAuthenticServer : public IlluminatePacketProcessor
{
public:
	CMRegisterNickNameToAuthenticServer() {};
	virtual ~CMRegisterNickNameToAuthenticServer() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};

