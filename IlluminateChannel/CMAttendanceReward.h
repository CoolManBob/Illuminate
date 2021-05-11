#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMAttendanceReward : public IlluminatePacketProcessor
{
public:
	CMAttendanceReward() {};
	virtual ~CMAttendanceReward() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
