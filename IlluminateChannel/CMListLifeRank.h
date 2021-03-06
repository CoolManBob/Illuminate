#pragma once
#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMListLifeRank : public IlluminatePacketProcessor
{
public:
	CMListLifeRank() {};
	virtual ~CMListLifeRank() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
