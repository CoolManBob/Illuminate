#pragma once

#include <string>

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class SMFixedCharge : public IlluminatePacketProcessor
{
public:
	SMFixedCharge() {};
	virtual ~SMFixedCharge() {};

	virtual bool processPacket(const localInfo& local);
};