#include "SMLoginUserToAuthenticServer.h"

bool SMLoginUserToAuthenticServer::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* outBound = localObj.packet;

	Int8 i8unk1, i8unk2;
	Int32 cookie, serverVer = 4635;
	*outBound << cookie;
	*outBound << i8unk1; //Family name, but why is it in int8???
	*outBound << i8unk2;
	*outBound << serverVer;

	return true;
}