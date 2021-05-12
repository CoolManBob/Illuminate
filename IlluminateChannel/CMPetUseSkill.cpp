#include "CMPetUseSkill.h"

bool CMPetUseSkill::processPacket(const localInfo& local)
{
    localInfo& localObj = const_cast<localInfo&>(local);
    IlluminatePacket* inPacket = localObj.packet;

    Int16 i16unk1, i16unk2, i16unk3;
    Int32 i32unk1, actorSessionId;
    Int64 petObjId;

    *inPacket >> petObjId;
    *inPacket >> i32unk1;
    *inPacket >> actorSessionId;
    *inPacket >> i16unk1;
    *inPacket >> i16unk2;
    *inPacket >> i16unk3;

    /* Implement Logic here */

    /*
    public void runImpl() {
        final Player player = ((GameClient) this.getClient()).getPlayer();
        if (player != null && this.bodySessionId > 0) {
            final Servant pet = player.getServantController().getServant(this.petObjId);
            if (pet != null && pet.getServantState() == EServantState.Field) {
                final DeadBody deadBody = KnowList.getObject(player, ECharKind.Deadbody, this.bodySessionId);
                if (deadBody != null) {
                    deadBody.pickupDrop(player);
                    player.sendPacket(new SMPetUseSkill(this.petObjId, this.bodySessionId));
                }
            }
        }
    }*/

    return true;
}