#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMEnchantItem : public IlluminatePacketProcessor
{
public:
	CMEnchantItem() {};
	virtual ~CMEnchantItem() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
