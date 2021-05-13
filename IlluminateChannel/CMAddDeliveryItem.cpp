#include "CMAddDeliveryItem.h"

bool CMAddDeliveryItem::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int16 originTownId, destinationTownId, carriageId, itemId, enchantLevel;
	Int64 itemObjId, itemCount, silverObjId;

	*inPacket >> originTownId;
	*inPacket >> destinationTownId;
	*inPacket >> carriageId;
	*inPacket >> itemId;
	*inPacket >> enchantLevel;
	*inPacket >> itemObjId;
	*inPacket >> itemCount;
	*inPacket >> silverObjId;

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
		}
	}*/

	return true;
}