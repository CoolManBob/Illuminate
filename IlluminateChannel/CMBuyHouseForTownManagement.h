#pragma once
#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMBuyHouseForTownManagement : public IlluminatePacketProcessor
{
public:
	CMBuyHouseForTownManagement() {};
	virtual ~CMBuyHouseForTownManagement() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
