#include "CMChangeGuildJoinMode.h"

bool CMChangeGuildJoinMode::processPacket(const localInfo& local)
{
    localInfo& localObj = const_cast<localInfo&>(local);
    IlluminatePacket* inPacket = localObj.packet;

    Int32 modeId;

    *inPacket >> modeId;

    /* Implement Logic here */

    /*
    public void runImpl() {
        final Player player = ((GameClient) this.getClient()).getPlayer();
        if (player != null && player.getGuild() == null) {
            GuildService.getInstance().changeGuildJoinMode(player, this.modeId);
        }
    }*/

    return true;
}