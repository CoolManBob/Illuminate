#pragma once
#include "IlluminateTypes.h"
//#include "IlluminateFlagLengthLookup.h"
//#include "IlluminateFieldLookup.h"
#include "IlluminatePacketPool.h"

#include <cstdarg>

//Main interface for interacting with incoming/outgoing packets
class IlluminatePacketInterface 
{
public:
	IlluminatePacketInterface();
	~IlluminatePacketInterface();

	IlluminatePacket * buildPacket(UInt16 packetType, ...);
	IlluminatePacket * buildMiniPacket(UInt16 miniType, ...);

	bool processPacket(IlluminatePacket * packet, ...);
	bool setupPkt(IlluminatePacket * packet); //Sets PacketType, FlagLength, and Field information for incoming packets.
private:
	/*IlluminateFlagLengthLookup flagLookup;
	IlluminateFieldLookup fieldLookup;*/
};