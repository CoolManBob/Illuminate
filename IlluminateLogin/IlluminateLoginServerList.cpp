#include "IlluminateLoginServerSystems.h"
#include "IlluminateLoginServerList.h"

bool IlluminateLoginServerList::processPacket(const localInfo& local)
{
	//AuPacket::GetField(&this->m_csPacket, 1, v8, v7, &pvPacket, &nSize, &Src, &nStatus, &pszEncodedWorld);
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* packet = localObj.packet;
	Int8 i8Operation = 0;
	char unkChar[32] = { 0 }, unkChar2[32] = { 0 };
	Int16 i16EncodedSize = 0;
	UInt32 i32Size = 0;
	char * encodedWorld = nullptr;
	//Int16 i16Status = 0;
	//int Src = 0;
	//int nStatus;
	
	//{	Illuminate::INT8, Illuminate::CHAR, Illuminate::INT16, Illuminate::MEMORY_BLOCK, Illuminate::CHAR }
	//{	1, 32, 1, 1, 32 }
	pktInterface->processPacket(packet, &i8Operation, unkChar, &i16EncodedSize, &i32Size, encodedWorld, unkChar2);

	switch (i8Operation)
	{
		case SERVERLIST_REQ: //ServerList Request Packet Opcode
			return processServerList(localObj); break;
		case 3:
			return processServerExtra(localObj); break;
		default:
		{
			stringstream errorMsg;
			errorMsg << "Server List processPacket Unhandled Operation: " << (int)i8Operation;
			LOG(errorMsg.str(), FATAL);
			return false;
		}
	}
	return false;
}

bool IlluminateLoginServerList::processServerList(localInfo& local)
{
	Int8 i8Operation = SERVERLIST_ANS;

	string worldListStr = serverListSys->buildWorldInfoStr();
	if (worldListStr == "ERROR")
	{
		LOG("processServerList: BAD worlistListStr", FATAL);
		return false;
	}
	UInt32 worldListLen = worldListStr.length()+1;
	
	SharedPtr<IlluminatePacket> serverList = pktInterface->buildPacket(Illuminate::AGPMWORLD_PACKET_TYPE, &i8Operation, 0, 0, &worldListLen, worldListStr.c_str(), 0);

	_localSock.sendPacket(serverList);

	return true;
}

bool IlluminateLoginServerList::processServerExtra(localInfo& local)
{
	return true;
}