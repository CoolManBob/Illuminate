#include "CMListLifeRank.h"

bool CMListLifeRank::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int32 rankingType; //& 0xFF

	*inPacket >> rankingType; //Ranking Type LifeSkills, Levels and RBF

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
			player.sendPacket(new SMListLifeRank(LifeRankService.getInstance().getTopPlayerRanks(this.lifeExpType), this.lifeExpType, player));
		}
	}*/

	IlluminatePacket* SMListLifeRankPkt = new IlluminatePacket(Illuminate::SMListLifeRank); //LifeRankService.getInstance().getTopPlayerRanks(this.lifeExpType), this.lifeExpType, player

	return true;
}