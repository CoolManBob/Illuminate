#include "CMChangePartyLeader.h"

bool CMChangePartyLeader::processPacket(const localInfo& local)
{
    localInfo& localObj = const_cast<localInfo&>(local);
    IlluminatePacket* inPacket = localObj.packet;

    Int32 partyObjId;

    *inPacket >> partyObjId; //Ranking Type LifeSkills, Levels and RBF

    /* Implement Logic here */

    /*
    public void runImpl() {
        final Player oldOwner = ((GameClient) this.getClient()).getPlayer();
        if (oldOwner != null) {
            final Player newOwner = World.getInstance().getPlayer(this.gameObjId);
            if (newOwner != null) {
                final IParty<Player> party = oldOwner.getParty();
                if (party != null) {
                    party.onEvent(new ChangePartyLeaderEvent(party, oldOwner, newOwner));
                }
            }
        }
    }*/

    return true;
}