#pragma once
#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMDeleteFriend : public IlluminatePacketProcessor
{
public:
	CMDeleteFriend() {};
	virtual ~CMDeleteFriend() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
