#include "CMAddFriend.h"

bool CMAddFriend::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	bool isName;
	std::string strData, charNameOrFamily;
	charNameOrFamily.reserve(62);

	*inPacket >> charNameOrFamily; //Name and or family name of adding player
	*inPacket >> isName;

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
			player.getFriendHandler().onEvent(new AddFriendEvent(player, this.nameOrFamily, this.isName));
		}
	}*/

	return true;
}