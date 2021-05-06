#include "CMDeleteFriend.h"

bool CMDeleteFriend::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int64 accountId;

	*inPacket >> accountId; //Player account Id being unfriended

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
			player.getFriendHandler().onEvent(new DeleteFriendEvent(player, this.accountId));
		}
	}*/

	return true;
}