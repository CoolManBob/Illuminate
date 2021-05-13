#include "CMBuyHouseForTownManagement.h"

bool CMBuyHouseForTownManagement::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int16 houseId;
	Int32 recipeUsageType, residenceLevel;

	*inPacket >> houseId; //ID of property being purchased
	*inPacket >> recipeUsageType; // What is house used for, residence, or a specific craft
	*inPacket >> residenceLevel; // What level is this workshop

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
			player.getHouseStorage().onEvent(new BuyHouseForTownManagementEvent(player, this.houseId, this.receipeKey));
		}
	}*/

	return true;
}