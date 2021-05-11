#include "CMAddFriendGroup.h"

bool CMAddFriendGroup::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	std::string strData, groupName;
	groupName.reserve(62);

	*inPacket >> groupName; //Name of friend group

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
			player.getFriendHandler().onEvent(new AddFriendGroupEvent(player, this.name));
		}
	}*/

	return true;
}