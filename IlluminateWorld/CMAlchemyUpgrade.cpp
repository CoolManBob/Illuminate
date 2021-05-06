#include "CMAlchemyUpgrade.h"

bool CMAlchemyUpgrade::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int8 storageLocation, stoneStorageLocation;
	Int32 slotIndex, stoneSlotIndex;
	Int64 count;
	*inPacket >> storageLocation;  // Call player storage (inventory)
	*inPacket >> slotIndex; // Counts inventory slots
	*inPacket >> count; // How many alchemy stones ? Seems a bit redundent considering they dont stack
	*inPacket >> stoneStorageLocation; // Alchemy stone current EXP?
	*inPacket >> stoneSlotIndex; // check what slot the alchemy stone is in

	/* Implement Logic here */

	/*
	public void runImpl() {
        final Player player = ((GameClient) this.getClient()).getPlayer();
        if (player != null) {
            player.getPlayerBag().onEvent(new AlchemyUpgradeItemEvent(player, this.stoneStorageLocation, this.storageLocation, this.stoneSlotIndex, this.slotIndex, this.count));
        }
    }*/

	return true;
}