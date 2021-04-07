#pragma once

#include <Poco/Foundation.h>
#include <Poco/SharedPtr.h>

using Poco::SharedPtr;

#include "IlluminatePool.h"
#include "IlluminatePacket.h"


class IlluminatePacketPool
{
public:
	IlluminatePacketPool();
	IlluminatePacketPool(int accessThreshold);
	~IlluminatePacketPool();

	void addPacketToPool(IlluminatePacket* pkt);
	size_t	getSize() { return packetPool->size(); }

private:
	UInt64 packetID;
	IlluminatePool<int, SharedPtr<IlluminatePacket>> * packetPool;
};