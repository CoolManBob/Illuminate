#include "CMAttendanceReward.h"

bool CMAttendanceReward::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int16 eventId; //HD & 0xFFFF;

	*inPacket >> eventId; //Ranking Type LifeSkills, Levels and RBF

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
			player.getPlayerBag().onEvent(new AttendanceItemEvent(player, this.eventId));
		}
	}*/

	return true;
}