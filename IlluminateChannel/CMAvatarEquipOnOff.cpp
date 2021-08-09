#include "CMAvatarEquipOnOff.h"

bool CMAvatarEquipOnOff::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int32 avatarEquip;

	*inPacket >> avatarEquip;  // toggle if on or off for cosmetic 

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
			player.setAvatarEquip(this.avatarEquip);
			player.sendBroadcastItSelfPacket(new SMAvataEquipOnOff(player));
		}
	}*/

	return true;
}