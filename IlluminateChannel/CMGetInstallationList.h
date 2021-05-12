#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMGetInstallationList : public IlluminatePacketProcessor
{
public:
	CMGetInstallationList() {};
	virtual ~CMGetInstallationList() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
#pragma once
