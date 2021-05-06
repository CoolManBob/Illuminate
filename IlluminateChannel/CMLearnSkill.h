#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMLearnSkill : public IlluminatePacketProcessor
{
public:
	CMLearnSkill() {};
	virtual ~CMLearnSkill() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
