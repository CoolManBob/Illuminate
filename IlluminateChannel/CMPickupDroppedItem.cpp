#include "CMPickupDroppedItem.h"

bool CMPickupDroppedItem::processPacket(const localInfo& local)
{
    localInfo& localObj = const_cast<localInfo&>(local);
    IlluminatePacket* inPacket = localObj.packet;

    Int8 i8unk1, i8unk2, i8unk3, i8unk4, i8unk5, slotIndex;
    Int32 sessionId, actorSessionId;
    Int64 itemCount;

    *inPacket >> i8unk1;
    *inPacket >> sessionId;
    *inPacket >> i8unk2;
    *inPacket >> actorSessionId;
    *inPacket >> i8unk3;
    *inPacket >> i8unk4;
    *inPacket >> i8unk5;
    *inPacket >> slotIndex;
    *inPacket >> itemCount;

    /* Implement Logic here */

    /*
    public void runImpl() {
        final Player player = ((GameClient) this.getClient()).getPlayer();
        if (player != null) {
            if (this.bodySessionId > 0) {
                final DeadBody deadBody = KnowList.getObject(player, ECharKind.Deadbody, this.bodySessionId);
                if (deadBody != null) {
                    deadBody.pickupDrop(player, this.slotIndex, this.count);
                }
            } else {
                player.getPlayerBag().onEvent(new PickupDroppedItemEvent(player, player.getPlayerBag().getDropBag(), this.slotIndex, 1, this.count));
            }
        }
    }*/

    return true;
}