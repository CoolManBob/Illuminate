#pragma once
#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMChangeGuildMemberGrade : public IlluminatePacketProcessor
{
public:
	CMChangeGuildMemberGrade() {};
	virtual ~CMChangeGuildMemberGrade() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
#pragma once
