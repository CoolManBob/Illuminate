#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMAlchemyUpgrade : public IlluminatePacketProcessor
{
public:
	CMAlchemyUpgrade() {};
	virtual ~CMAlchemyUpgrade() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
