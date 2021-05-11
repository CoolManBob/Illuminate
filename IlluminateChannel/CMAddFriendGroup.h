#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMAddFriendGroup : public IlluminatePacketProcessor
{
public:
	CMAddFriendGroup() {};
	virtual ~CMAddFriendGroup() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
#pragma once
#pragma once
