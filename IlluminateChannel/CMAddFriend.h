#pragma once
#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMAddFriend : public IlluminatePacketProcessor
{
public:
	CMAddFriend() {};
	virtual ~CMAddFriend() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
