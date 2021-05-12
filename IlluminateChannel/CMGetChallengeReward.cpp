#include "CMGetChallengeReward.h"

bool CMGetChallengeReward::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int16 challengeId, selectedItem;

	*inPacket >> challengeId;
	*inPacket >> selectedItem;

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
			player.getChallengeHandler().reward(this.challengeId, this.selectIndex);
		}
	}*/

	return true;
}