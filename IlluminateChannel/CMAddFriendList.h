#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMAddFriendList : public IlluminatePacketProcessor
{
public:
	CMAddFriendList() {};
	virtual ~CMAddFriendList() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
#pragma once
