#include "CMRenameFriendGroup.h"

bool CMRenameFriendGroup::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int32 groupId;
	std::string strData, groupName;
	groupName.reserve(62);

	*inPacket >> groupName; //Name of friend group
	*inPacket >> groupId; //ID of friend group

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
			player.getFriendHandler().onEvent(new RenameFriendGroupEvent(player, this.groupId, this.name));
		}
	}*/
	IlluminatePacket* SMRenameFriendGroupPkt = new IlluminatePacket(Illuminate::SMRenameFriendGroup);

	return true;
}