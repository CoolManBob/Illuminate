#include "CMChangeAwakenSkill.h"

bool CMChangeAwakenSkill::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int8 storageLocation, slotIndex, i8unk1;
	Int16 oldSkillId, newSkillId;
	Int32 abilityId, npcGameObjId;

	*inPacket >> oldSkillId;
	*inPacket >> newSkillId;
	*inPacket >> abilityId;
	*inPacket >> storageLocation;
	*inPacket >> slotIndex;
	*inPacket >> npcGameObjId;
	*inPacket >> i8unk1;

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