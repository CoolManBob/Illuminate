#pragma once

#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMGetCreateUserInformationToAuthenticServer : public IlluminatePacketProcessor
{
public:
	CMGetCreateUserInformationToAuthenticServer() {};
	virtual ~CMGetCreateUserInformationToAuthenticServer() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};