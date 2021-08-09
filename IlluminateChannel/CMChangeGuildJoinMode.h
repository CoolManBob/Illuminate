#pragma once
#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMChangeGuildJoinMode : public IlluminatePacketProcessor
{
public:
	CMChangeGuildJoinMode() {};
	virtual ~CMChangeGuildJoinMode() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
