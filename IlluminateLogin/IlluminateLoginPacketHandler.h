#pragma once

#include "IlluminatePacketHandler.h"

//Packet Handlers
#include "PacketHandlers/CMGetCreateUserInformationToAuthenticServer.h"

class IlluminateLoginPacketHandler : public IlluminatePacketHandler
{
public:
	IlluminateLoginPacketHandler() : packetHandler(this, &IlluminateLoginPacketHandler::packetProcessor) 
	{
		/*processorMap[Illuminate::AGPMLOGIN_PACKET_TYPE]				= new IlluminateLoginClientLogin();
		processorMap[Illuminate::AGPMWORLD_PACKET_TYPE]				= new IlluminateLoginServerList();
		processorMap[Illuminate::AGPMSTARTUPENCRYPTION_PACKET_TYPE]	= new IlluminateLoginStartupEncryption();*/
		processorMap[Illuminate::CMGetCreateUserInformationToAuthenticServer] = new CMGetCreateUserInformationToAuthenticServer();
		
	}
	virtual ~IlluminateLoginPacketHandler() { processorMap.clear(); };

	ActiveMethod<bool, localInfo, IlluminateLoginPacketHandler, ActiveStarter<ActiveDispatcher>> packetHandler;

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