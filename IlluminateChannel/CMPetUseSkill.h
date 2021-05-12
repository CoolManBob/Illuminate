#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMPetUseSkill : public IlluminatePacketProcessor
{
public:
	CMPetUseSkill() {};
	virtual ~CMPetUseSkill() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
