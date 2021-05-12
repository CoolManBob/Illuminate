#pragma once
#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMListWarehouseItem : public IlluminatePacketProcessor
{
public:
	CMListWarehouseItem() {};
	virtual ~CMListWarehouseItem() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
#pragma once
