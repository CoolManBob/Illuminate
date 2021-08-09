#include "CMChangeFormServant.h"

bool CMChangeFormServant::processPacket(const localInfo& local)
{
    localInfo& localObj = const_cast<localInfo&>(local);
    IlluminatePacket* inPacket = localObj.packet;

    Int8 storageLocation, itemSlot, i8unk1;
    Int16 formIndex;
    Int32 npcSessionId;
    Int64 servantObjectId;

    *inPacket >> servantObjectId;
    *inPacket >> npcSessionId;
    *inPacket >> formIndex;
    *inPacket >> storageLocation;
    *inPacket >> itemSlot;
    *inPacket >> i8unk1;

    /* Implement Logic here */

    /*
    public void runImpl() {
        final Player player = ((GameClient) this.getClient()).getPlayer();
        if (player != null) {
            final Npc npc = KnowList.getObject(player, ECharKind.Npc, this.npcSessionId);
            if (npc == null) {
                return;
            }
            final Servant servant = player.getServantController().getServant(this.servantObjectId);
            if (servant != null && servant.getServantState().isStable() && servant.getRegionId() == npc.getRegionId()) {
                player.getPlayerBag().onEvent(new ChangeFormServantEvent(player, servant, this.formIndex, this.itemStorageLocation, this.itemSlot));
            }
        }
    }*/

    return true;
}