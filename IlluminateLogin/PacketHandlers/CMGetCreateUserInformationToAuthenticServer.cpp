#include "CMGetCreateUserInformationToAuthenticServer.h"

bool CMGetCreateUserInformationToAuthenticServer::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	string data;
	data.reserve(2050);
	Int32 cookie, clientVer, unk;
	*inPacket >> data;
	*inPacket >> cookie;
	*inPacket >> clientVer;
	*inPacket >> unk;
	//data.replace()

	extraPacketProcessing(localObj, clientVer);

	IlluminatePacket* outPacket = new IlluminatePacket(Illuminate::SMGetCreateUserInformationToAuthenticServer);
	
	int value = 0;
	*outPacket << value;

	local.sock.sendPacket(outPacket);

	return true;
}

bool CMGetCreateUserInformationToAuthenticServer::extraPacketProcessing(localInfo& local, int& data)
{
	//do stuff
	data = 2;
	return true;
}