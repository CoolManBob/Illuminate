#include "CMAcceptAddFriend.h"

bool CMAcceptAddFriend::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int64 accountId;

	*inPacket >> accountId; //Player who has sent the request accountId

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
			player.getFriendHandler().onEvent(new AcceptAddFriendEvent(player, this.accountId));
		}
	}*/
	IlluminatePacket* SMAcceptAddFriend = new IlluminatePacket(Illuminate::SMAcceptAddFriend);

	return true;
}