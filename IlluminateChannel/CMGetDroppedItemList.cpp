#include "CMGetDroppedItemList.h"

bool CMGetDroppedItemList::processPacket(const localInfo& local)
{
    localInfo& localObj = const_cast<localInfo&>(local);
    IlluminatePacket* inPacket = localObj.packet;

    Int32 actorSessionId;

    *inPacket >> actorSessionId;


    /* Implement Logic here */

    /*
    public void runImpl() {
        final Player player = ((GameClient) this.getClient()).getPlayer();
        if (player != null) {
            final DeadBody deadBody = KnowList.getObject(player, ECharKind.Deadbody, this.bodySessionId);
            if (deadBody != null && !deadBody.dropIsEmpty()) {
                player.sendPacket(new SMGetDroppedItems(this.bodySessionId, deadBody.getDropBag()));
            }
        }
    }*/

    return true;
}