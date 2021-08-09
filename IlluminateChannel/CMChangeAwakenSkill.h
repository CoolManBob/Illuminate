#pragma once
#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMChangeAwakenSkill : public IlluminatePacketProcessor
{
public:
	CMChangeAwakenSkill() {};
	virtual ~CMChangeAwakenSkill() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
