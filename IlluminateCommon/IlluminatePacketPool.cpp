#include "IlluminatePacketPool.h"

IlluminatePacketPool::IlluminatePacketPool()
{
	packetID = 0;
	packetPool = new IlluminatePool<int, SharedPtr<IlluminatePacket>>();
}

IlluminatePacketPool::IlluminatePacketPool(int accessThreshold)
{
	packetID = 0;
	packetPool = new IlluminatePool<int, SharedPtr<IlluminatePacket>>(accessThreshold);
}

IlluminatePacketPool::~IlluminatePacketPool()
{
	if (packetPool)
	{
		packetPool->clear();
		delete packetPool;
	}
}

void IlluminatePacketPool::addPacketToPool(IlluminatePacket* pkt)
{
	SharedPtr<IlluminatePacket> sharedPkt(pkt);
	packetPool->add(packetID, sharedPkt);
	packetID++; //Since this is unsigned it doesn't matter if we let this eventually roll over (pro tip: its 64bits so it realistically will not.)
}