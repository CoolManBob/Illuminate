#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMGetDroppedItemList : public IlluminatePacketProcessor
{
public:
	CMGetDroppedItemList() {};
	virtual ~CMGetDroppedItemList() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
