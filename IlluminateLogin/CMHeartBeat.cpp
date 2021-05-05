#include "CMHeartBeat.h"

bool CMHeartBeat::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	int data;
	*inPacket >> data;

	extraPacketProcessing(localObj, data);

	IlluminatePacket* outPacket = new IlluminatePacket(Illuminate::SMHeartBeat); //No SMHeartBeat Packet guess we just drop this?

	int value = 0;
	*outPacket << value;

	local.sock.sendPacket(outPacket);

	return true;
}

bool CMGetHeartBeat::extraPacketProcessing(localInfo& local, int& data)
{

}