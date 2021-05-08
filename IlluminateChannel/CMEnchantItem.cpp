#include "CMEnchantItem.h"

bool CMEnchantItem::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int8 itemStorageType, stoneStorageType, cronStorageType;
	Int32 itemSlot, stoneSlot, cronSlot; // & 0xFF
	bool isPerfect; // & 0xFF
	
	*inPacket >> itemStorageType;
	*inPacket >> itemSlot;
	*inPacket >> stoneStorageType;
	*inPacket >> stoneSlot;
	*inPacket >> cronStorageType;
	*inPacket >> cronSlot;
	*inPacket >> isPerfect;

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
			player.getPlayerBag().onEvent(new EnchantItemEvent(player, this.itemStorageType, this.itemSlot, this.stoneStorageType, this.stoneSlot, this.croneStorageType, this.croneSlotIndex, this.isPerfect));
		}
	}*/

	return true;
}