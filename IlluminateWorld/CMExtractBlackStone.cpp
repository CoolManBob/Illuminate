#include "CMExtractBlackStone.h"

bool CMExtractBlackStone::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int8 ItemStorageLocation;
	Int32 itemSlot;

	*inPacket >> ItemStorageLocation; //Call player bag
	*inPacket >> itemSlot; //Slot where extracted item is located

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
			player.getPlayerBag().onEvent(new ExtractBlackStoneEvent(player, this.storageType, this.slotIndex));
		}
	}*/
	IlluminatePacket* SMExtractBlackStonePkt = new IlluminatePacket(Illuminate::SMExtractBlackStone); //We dont have a SM packet to send here

	return true;
}