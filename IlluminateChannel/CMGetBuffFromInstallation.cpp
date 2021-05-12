#include "CMGetBuffFromInstallation.h"

bool CMGetBuffFromInstallation::processPacket(const localInfo& local)
{
    localInfo& localObj = const_cast<localInfo&>(local);
    IlluminatePacket* inPacket = localObj.packet;

    Int64 houseObjId, installationObjId;

    *inPacket >> houseObjId;
    *inPacket >> installationObjId;

    /* Implement Logic here */

    /*
    public void runImpl() {
        final Player player = ((GameClient) this.getClient()).getPlayer();
        if (player != null) {
            player.getHouseStorage().onEvent(new GetBuffFromHouseInstallationEvent(player, this.houseObjId, this.installationObjId));
        }
    }*/

    return true;
}