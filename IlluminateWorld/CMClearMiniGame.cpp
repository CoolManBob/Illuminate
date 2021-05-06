#include "CMClearMiniGame.h"

bool CMClearMiniGame::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int16 miniGameId;
	Int32 i32unk1;

	*inPacket >> miniGameId;
	*inPacket >> i32unk1;

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
			player.getObserveController().notifyObserver(EObserveType.clearMiniGame, this.miniGameId);
		}
	}*/

	return true;
}