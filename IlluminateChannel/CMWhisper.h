#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMWhisper : public IlluminatePacketProcessor
{
public:
	CMWhisper() {};
	virtual ~CMWhisper() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once

