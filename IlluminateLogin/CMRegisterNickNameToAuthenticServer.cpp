#include "CMRegisterNickNameToAuthenticServer.h"
#include "IlluminateTypes.h"

bool CMRegisterNickNameToAuthenticServer::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	int data;
	*inPacket >> data;

	extraPacketProcessing(localObj, data);

	IlluminatePacket* outPacket = new IlluminatePacket(Illuminate::SMGetContentServiceInfo);
	IlluminatePacket* outPacket = new IlluminatePacket(Illuminate::SMRegisterNickNameToAuthenticServer);
	IlluminatePacket* outPacket = new IlluminatePacket(Illuminate::SMFixedCharge);
	IlluminatePacket* outPacket = new IlluminatePacket(Illuminate::SMGetWorldInformations);
	int value = 0;
	*outPacket << value;

	local.sock.sendPacket(outPacket);

	return true;
}

bool CMRegisterNickNameToAuthenticServer::extraPacketProcessing(localInfo& local, int& data)
{
	Int32 unk;
	Int32 value = 62; // 62 familyName
	IlluminatePacket * inPacket = localPkt;
	//The server doesn't actually need these two, should we bother handling their data or just handle as Unk? (int32)
	*inPacket >> unk; // Screen Width
	*inPacket >> unk; // Screen Height
	return true;
}