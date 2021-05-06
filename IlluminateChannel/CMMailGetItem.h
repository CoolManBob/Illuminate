#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMMailGetItem : public IlluminatePacketProcessor
{
public:
	CMMailGetItem() {};
	virtual ~CMMailGetItem() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};