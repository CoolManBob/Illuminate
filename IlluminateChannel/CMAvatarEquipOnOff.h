#pragma once
#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMAvatarEquipOnOff : public IlluminatePacketProcessor
{
public:
	CMAvatarEquipOnOff() {};
	virtual ~CMAvatarEquipOnOff() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
