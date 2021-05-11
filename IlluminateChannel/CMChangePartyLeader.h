#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMChangePartyLeader : public IlluminatePacketProcessor
{
public:
	CMChangePartyLeader() {};
	virtual ~CMChangePartyLeader() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
