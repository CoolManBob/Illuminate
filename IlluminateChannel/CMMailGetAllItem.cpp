#include "CMMailGetAllItem.h"

bool CMMailGetAllItem::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int64 mailObjectId, attachedItemObjectId, attachedItemCount;

	*inPacket >> mailObjectId; //Id of mail
	*inPacket >> attachedItemObjectId; // ID of attached Item
	*inPacket >> attachedItemCount; //Quanityt of attached Item

	/* Implement Logic here */

	/*
    public void runImpl() {
        final Player player = (this.getClient()).getPlayer();
        if (player != null) {
            if (player.getRegion().getTemplate().isSafe()) {
                player.getPlayerBag().onEvent(new MailGetSpecificItemEvent(player, _mailObjectId, _attachedItemObjectId));
            } else {
                player.sendPacket(new SMNak(EStringTable.eErrNoIsntSafeZone, this.opCode));
            }
        }
    }*/

	return true;
}