#pragma once

#include <string>

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class SMGetCreateUserInformationToAuthenticServer : public IlluminatePacketProcessor
{
public:
	SMGetCreateUserInformationToAuthenticServer() {};
	virtual ~SMGetCreateUserInformationToAuthenticServer() {};

	virtual bool processPacket(const localInfo& local);
};
#pragma once
