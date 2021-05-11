#include "CMAddFriendList.h"

bool CMAddFriendList::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;


	/* Implement Logic here */

	IlluminatePacket* SMAddFriendList = new IlluminatePacket(Illuminate::SMAddFriendList);

	/*
    public void runImpl() {
        final Player player = ((GameClient) this.getClient()).getPlayer();
        if (player != null) {
            this.sendPacket((SendablePacket) new SMAddFriendList(player.getFriendHandler().getFriendsReqList()));
        }
    }*/

	return true;
}