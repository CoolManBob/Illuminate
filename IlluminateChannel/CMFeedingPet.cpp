#include "CMChangeLooting.h"

bool CMChangeLooting::processPacket(const localInfo& local)
{
    localInfo& localObj = const_cast<localInfo&>(local);
    IlluminatePacket* inPacket = localObj.packet;

    Int8 feedType, feedItemSlot;
    Int64 petObjId;

    *inPacket >> petObjId; // Let's get the ID of the pet we are feeding
    *inPacket >> feedType; // Lets get what type of food we are using from the player controller storage
    *inPacket >> feedItemSlot; // Let's tell the server what slot we will be consuming the food is from

    /* Implement Logic here */

    /*
    public void runImpl() {
        final Player player = ((GameClient) this.getClient()).getPlayer();
        if (player != null) {
            player.getPlayerBag().onEvent(new FeedingPetItemEvent(player, this.petObjId, this.feedItemStorageType, this.feedItemSlot));
        }
    }*/

    return true;
}