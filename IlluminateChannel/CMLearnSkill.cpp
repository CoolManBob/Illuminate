#include "CMLearnSkill.h"

bool CMLearnSkill::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int16 SkillLevel, SkillId;
	Int32 Skillunk;

	*inPacket >> Skillunk; //Possibly class type?
	*inPacket >> SkillLevel; //Which level of skill is learned
	*inPacket >> SkillId; // ID of learned skill

	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
			player.getSkillList().learnSkill(this.skillId, false);
		}
	}*/

	return true;
}