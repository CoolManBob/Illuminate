#include "CMBattleHelmOnOff.h"

bool CMBattleHelmOnOff::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	bool EquipBattleHelmet;

	*inPacket >> EquipBattleHelmet;  // is the player in combat state if so = 1 else = 0

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
			player.getPlayerRenderStorage().setRender(ERenderType.HELM_IN_BATTLE, this.result);
		}
	}*/

	return true;
}