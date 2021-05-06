#include "SMFixedCharge.h"

bool SMFixedCharge::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* outBound = localObj.packet;
	
	Int8 i8unk1 = 0;
	Int64 i64unk1 = -2;
	
	*outBound << i64unk1;
	*outBound << i8unk1;

	return true;
}