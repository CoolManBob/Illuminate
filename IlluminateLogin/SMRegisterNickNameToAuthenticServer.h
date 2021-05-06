#pragma once

#include <string>

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class SMRegisterNickNameToAuthenticServer : public IlluminatePacketProcessor
{
public:
	SMRegisterNickNameToAuthenticServer() {};
	virtual ~SMRegisterNickNameToAuthenticServer() {};

	virtual bool processPacket(const localInfo& local);
};