#include "SMRegisterNickNameToAuthenticServer.h"

bool SMRegisterNickNameToAuthenticServer::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* outBound = localObj.packet;

	Int32 NickName = 26403848;

	*outBound << NickName;

	return true;
}