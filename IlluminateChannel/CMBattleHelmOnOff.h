#pragma once
#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMBattleHelmOnOff : public IlluminatePacketProcessor
{
public:
	CMBattleHelmOnOff() {};
	virtual ~CMBattleHelmOnOff() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
