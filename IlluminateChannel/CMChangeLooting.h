#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMChangeLooting : public IlluminatePacketProcessor
{
public:
	CMChangeLooting() {};
	virtual ~CMChangeLooting() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once

