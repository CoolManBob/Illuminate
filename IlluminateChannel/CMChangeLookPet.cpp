#include "CMChangeLookPet.h"

bool CMChangeLookPet::processPacket(const localInfo& local)
{
    localInfo& localObj = const_cast<localInfo&>(local);
    IlluminatePacket* inPacket = localObj.packet;

    Int8 formIndex;
    Int32 petNpcId, slotIndex, actionIndex;
    Int64 petObjectId;

    *inPacket >> petObjectId; //Get pets ID for current session
    *inPacket >> petNpcId; //Get pets type
    *inPacket >> formIndex; //Get our pet skins
    *inPacket >> slotIndex; //What slot is our pet in
    *inPacket >> actionIndex; //What is our pets current state?

    /* Implement Logic here */

    /*
    public void runImpl() {
        final Player player = ((GameClient) this.getClient()).getPlayer();
        if (player != null) {
            final Servant pet = player.getServantController().getServant(this.petObjectId);
            if (pet == null) {
                return;
            }
            if (pet.getCreatureId() != this.petNpcId) {
                return;
            }
            if (!PetChangeLookTable.getInstance().isPetActionIndexValid(pet.getPetTemplate().getPetChangeLookKey(), this.actionIndex)) {
                return;
            }
            player.getPlayerBag().onEvent(new ChangePetLookEvent(player, this.petObjectId, this.actionIndex, this.storageLocation, this.slotIndex));
        }
    }*/

    return true;
}