#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMPickupDroppedItem : public IlluminatePacketProcessor
{
public:
	CMPickupDroppedItem() {};
	virtual ~CMPickupDroppedItem() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
#pragma once
