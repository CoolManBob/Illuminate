#include "CMChangeGuildMemberGrade.h"

bool CMChangeGuildMemberGrade::processPacket(const localInfo& local)
{
    localInfo& localObj = const_cast<localInfo&>(local);
    IlluminatePacket* inPacket = localObj.packet;

    Int8 guildMemberRankType, i8unk1;
    Int64 accountId;
    
    *inPacket >> accountId;
    *inPacket >> guildMemberRankType;
    *inPacket >> i8unk1;

    /* Implement Logic here */

    /*
    public void runImpl() {
        final Player player = ((GameClient) this.getClient()).getPlayer();
        if (player != null) {
            final Guild guild = player.getGuild();
            if (guild != null) {
                guild.onEvent(new ChangeGuildMemberGradeEvent(player, guild, this.accountId, this.rank));
            }
        }
    }*/

    return true;
}