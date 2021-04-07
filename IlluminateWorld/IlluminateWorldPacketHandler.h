#pragma once

#include "IlluminatePacketHandler.h"

//Packet Handlers
#include "IlluminateWorldCharacter.h"
#include "IlluminateWorldAGSMCharMgr.h"
#include "IlluminateWorldUIStatus.h"
#include "IlluminateWorldOptimizedCharMove.h"
#include "IlluminateWorldStartupEncryption.h"


class IlluminateWorldPacketHandler : public IlluminatePacketHandler
{
public:
	IlluminateWorldPacketHandler() : packetHandler(this, &IlluminateWorldPacketHandler::packetProcessor)
	{
		processorMap[Illuminate::AGPMCHARACTER_PACKET_TYPE]			= new IlluminateWorldCharacter();
		processorMap[Illuminate::AGSMCHARMANAGER_PACKET_TYPE]			= new IlluminateWorldAGSMCharMgr();
		processorMap[Illuminate::AGPMUISTATUS_PACKET_TYPE]			= new IlluminateWorldUIStatus();
		processorMap[Illuminate::AGPMOPTIMIZEDCHARMOVE_PACKET_TYPE]	= new IlluminateWorldOptimizedCharMove();
		processorMap[Illuminate::AGPMSTARTUPENCRYPTION_PACKET_TYPE]	= new IlluminateWorldStartupEncryption();
	}
	virtual ~IlluminateWorldPacketHandler() {};

	ActiveMethod<bool, localInfo, IlluminateWorldPacketHandler, ActiveStarter<ActiveDispatcher>> packetHandler;

private:
	bool packetProcessor(const localInfo &local)
	{
		HashMap<Int16, IlluminatePacketProcessor*>::Iterator Itr = processorMap.find(local.packet->GetPacketType());
		if (Itr != processorMap.end())
		{
			return Itr->second->processPacket(local);
		}
		else
		{
			return false;
		}
	}

	HashMap<Int16, IlluminatePacketProcessor*> processorMap;
};