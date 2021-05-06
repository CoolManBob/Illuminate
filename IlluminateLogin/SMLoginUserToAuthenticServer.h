#pragma once

#include <string>

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class SMLoginUserToAuthenticServer : public IlluminatePacketProcessor
{
public:
	SMLoginUserToAuthenticServer() {};
	virtual ~SMLoginUserToAuthenticServer() {};

	virtual bool processPacket(const localInfo& local);
};
