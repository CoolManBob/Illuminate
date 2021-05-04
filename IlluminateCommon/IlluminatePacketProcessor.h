#pragma once

#include "IlluminateLocalInfo.h"
#include "IlluminateBDOCrypt.h"

class IlluminatePacketProcessor
{
public:
	IlluminatePacketProcessor() {};
	IlluminatePacketProcessor(IlluminatePacket* packet) { /*processPacket(packet);*/ };
	virtual ~IlluminatePacketProcessor() {};

	//virtual bool processPacket(IlluminateSocket& sock, IlluminatePacket* packet) { return true; };
	virtual bool processPacket(const localInfo& info) { return true; };
};