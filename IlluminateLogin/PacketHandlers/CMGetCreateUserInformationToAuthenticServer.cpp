#include "CMGetCreateUserInformationToAuthenticServer.h"

bool CMGetCreateUserInformationToAuthenticServer::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	int data;
	*inPacket >> data;

	extraPacketProcessing(localObj, data);

	IlluminatePacket* outPacket = new IlluminatePacket(Illuminate::SMGetCreateUserInformationToAuthenticServer);
	
	int value = 0;
	*outPacket << value;

	local.sock.sendPacket(outPacket);

	return true;
}

bool CMGetCreateUserInformationToAuthenticServer::extraPacketProcessing(localInfo& local, int& data)
{
	string data;
	data.reserve(2050);
	Int32 cookie, clientVer, unk;
	*inPacket >> data;
	*inPacket >> cookie;
	*inPacket >> clientVer;
	*inPacket >> unk;
}