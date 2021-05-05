#pragma once

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMHeartBeat : public IlluminatePacketProcessor
{
public:
	CMHeartBeat() {};
	virtual ~CMHeartBeat() {};

	virtual bool processPacket(const localInfo& local);
};
