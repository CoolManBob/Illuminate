#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMRenameFriendGroup : public IlluminatePacketProcessor
{
public:
	CMRenameFriendGroup() {};
	virtual ~CMRenameFriendGroup() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};

