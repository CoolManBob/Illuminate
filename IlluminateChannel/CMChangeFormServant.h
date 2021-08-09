#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMChangeFormServant : public IlluminatePacketProcessor
{
public:
	CMChangeFormServant() {};
	virtual ~CMChangeFormServant() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once