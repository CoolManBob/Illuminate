#pragma once

#include "Poco/Foundation.h"
#include "Poco/ActiveDispatcher.h"
#include "Poco/ActiveMethod.h"
#include "Poco/ActiveStarter.h"
#include "Poco/HashMap.h"
#include "Poco/Void.h"

#include "IlluminateLocalInfo.h"

#include "IlluminatePacketProcessor.h"
#include "IlluminateBDOCrypt.h"

using namespace Poco;

class IlluminatePacketHandler : public ActiveDispatcher
{
public:
	IlluminatePacketHandler() : packetHandler(this, &IlluminatePacketHandler::packetProcessor) {};
	virtual ~IlluminatePacketHandler() {};

private:

	bool packetProcessor(const localInfo &local)
	{
		HashMap<Int16, IlluminatePacketProcessor*>::Iterator Itr = processorMap.find(local.packet->GetOpCode());
		if (Itr != processorMap.end())
		{
			return Itr->second->processPacket(local);
		}
		else
			return false;
	}

	ActiveMethod<bool, localInfo, IlluminatePacketHandler, ActiveStarter<ActiveDispatcher>> packetHandler;
	HashMap<Int16, IlluminatePacketProcessor*> processorMap;
};