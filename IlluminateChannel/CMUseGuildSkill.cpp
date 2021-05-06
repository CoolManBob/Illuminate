#include "CMUseGuildSkill.h"

bool CMUseGuildSkill::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int16 SkillLevel, SkillId, i16unk1;

	*inPacket >> SkillId; // ID of learned skill
    *inPacket >> SkillLevel; //Which level of skill is learned
    *inPacket >> i16unk1; //Possibly cooltime? //Need to make HD | & 0xFFFF

	/* Implement Logic here */

	/*
    public void runImpl() {
        final Player player = ((GameClient) this.getClient()).getPlayer();
        if (player != null && player.getGuildMemberRankType().isMaster()) {
            final Guild guild = player.getGuild();
            if (guild != null) {
                final SkillT skillT = guild.getGuildSkillList().getSkill(this.skillId);
                if (skillT != null && skillT.getSkillType().isActive()) {
                    for (final Player member : guild.getMembersOnline()) {
                        SkillService.useSkill(player, skillT, null, Collections.singletonList(member));
                    }
                }
            }
        }
    }*/

	return true;
}