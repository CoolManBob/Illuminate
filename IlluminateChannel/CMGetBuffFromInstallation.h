#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMGetBuffFromInstallation : public IlluminatePacketProcessor
{
public:
	CMGetBuffFromInstallation() {};
	virtual ~CMGetBuffFromInstallation() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
