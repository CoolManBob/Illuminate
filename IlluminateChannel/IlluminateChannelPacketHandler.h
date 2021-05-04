#pragma once

#include "IlluminatePacketHandler.h"

//Packet Handlers
/*#include "IlluminateChannelCharacter.h"
#include "IlluminateChannelAGSMCharMgr.h"
#include "IlluminateChannelUIStatus.h"
#include "IlluminateChannelOptimizedCharMove.h"
#include "IlluminateChannelStartupEncryption.h"*/


class IlluminateChannelPacketHandler : public IlluminatePacketHandler
{
public:
	IlluminateChannelPacketHandler() : packetHandler(this, &IlluminateChannelPacketHandler::packetProcessor)
	{
		/*processorMap[Illuminate::AGPMCHARACTER_PACKET_TYPE]			= new IlluminateChannelCharacter();
		processorMap[Illuminate::AGSMCHARMANAGER_PACKET_TYPE]			= new IlluminateChannelAGSMCharMgr();
		processorMap[Illuminate::AGPMUISTATUS_PACKET_TYPE]			= new IlluminateChannelUIStatus();
		processorMap[Illuminate::AGPMOPTIMIZEDCHARMOVE_PACKET_TYPE]	= new IlluminateChannelOptimizedCharMove();
		processorMap[Illuminate::AGPMSTARTUPENCRYPTION_PACKET_TYPE]	= new IlluminateChannelStartupEncryption();*/
	}
	virtual ~IlluminateChannelPacketHandler() {};

	ActiveMethod<bool, localInfo, IlluminateChannelPacketHandler, ActiveStarter<ActiveDispatcher>> packetHandler;

private:
	bool packetProcessor(const localInfo &local)
	{
		HashMap<Int16, IlluminatePacketProcessor*>::Iterator Itr = processorMap.find(local.packet->GetOpCode());
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