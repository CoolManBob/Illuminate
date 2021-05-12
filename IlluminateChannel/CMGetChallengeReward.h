#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMGetChallengeReward : public IlluminatePacketProcessor
{
public:
	CMGetChallengeReward() {};
	virtual ~CMGetChallengeReward() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
#pragma once
