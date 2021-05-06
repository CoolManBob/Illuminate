#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMExtractBlackStone : public IlluminatePacketProcessor
{
public:
	CMExtractBlackStone() {};
	virtual ~CMExtractBlackStone() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
