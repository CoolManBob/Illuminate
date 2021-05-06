#include "CMMailGetItem.h"

bool CMMailGetItem::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int8 storageLocation;
	Int64 id, count, expireDate;

	*inPacket >> id; //MailId in Database
	*inPacket >> count; //How many mails does the player have?
	*inPacket >> expireDate; // Date the mail which will expire and the server should drop the mail
	*inPacket >> storageLocation; //Get mail from Database storage

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null && player.getRegion().getTemplate().isSafe()) {
			player.getPlayerBag().onEvent(new MailGetItemEvent(player, this.id, this.count, this.storageLocation));
		}
	}*/

	return true;
}