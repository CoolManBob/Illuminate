#include "CMRegisterNickNameToAuthenticServer.h"

bool CMRegisterNickNameToAuthenticServer::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int32 unk;
	Int32 value = 62; // 62 familyName
	//The server doesn't actually need these two, should we bother handling their data or just handle as Unk? (int32)
	*inPacket >> unk; // Screen Width
	*inPacket >> unk; // Screen Height


	IlluminatePacket* SMContentServicePkt = new IlluminatePacket(Illuminate::SMGetContentServiceInfo);
	IlluminatePacket* SMNickNamePkt = new IlluminatePacket(Illuminate::SMRegisterNickNameToAuthenticServer);
	IlluminatePacket* SMFixedChargePkt = new IlluminatePacket(Illuminate::SMFixedCharge);
	IlluminatePacket* SMWorldInfoPacket = new IlluminatePacket(Illuminate::SMGetWorldInformations);

	//local.sock.sendPacket(outPacket);

	return true;
}