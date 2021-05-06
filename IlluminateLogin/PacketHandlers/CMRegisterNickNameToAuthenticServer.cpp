#include "CMRegisterNickNameToAuthenticServer.h"

bool CMRegisterNickNameToAuthenticServer::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int32 ScreenH, ScreenW;
	std::string familyName;
	familyName.reserve(62);
	*inPacket >> familyName;  // 62 familyName
	*inPacket >> ScreenH; // Screen Width
	*inPacket >> ScreenW; // Screen Height

	IlluminatePacket* SMContentServicePkt = new IlluminatePacket(Illuminate::SMGetContentServiceInfo);
	IlluminatePacket* SMNickNamePkt = new IlluminatePacket(Illuminate::SMRegisterNickNameToAuthenticServer);
	IlluminatePacket* SMFixedChargePkt = new IlluminatePacket(Illuminate::SMFixedCharge);
	IlluminatePacket* SMWorldInfoPacket = new IlluminatePacket(Illuminate::SMGetWorldInformations);

	//local.sock.sendPacket(outPacket);

	return true;
}