#pragma once
#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMAcceptAddFriend : public IlluminatePacketProcessor
{
public:
	CMAcceptAddFriend() {};
	virtual ~CMAcceptAddFriend() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
