#pragma once

#include <string>

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class SMGetContentServiceInfo : public IlluminatePacketProcessor
{
public:
	SMGetContentServiceInfo() {};
	virtual ~SMGetContentServiceInfo() {};

	virtual bool processPacket(const localInfo& local);
};