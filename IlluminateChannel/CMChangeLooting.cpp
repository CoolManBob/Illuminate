#include "CMChangeLooting.h"

bool CMChangeLooting::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int8 lootingType;

	*inPacket >> lootingType; //Ranking Type LifeSkills, Levels and RBF

	/* Implement Logic here */

	/*
    public void runImpl() {
        final EPartyLootType lootType = EPartyLootType.valueOf(this.lootingType);
        if (lootType == null) {
            return;
        }
        final Player owner = ((GameClient) this.getClient()).getPlayer();
        if (owner != null) {
            final IParty<Player> party = owner.getParty();
            if (party != null) {
                party.onEvent(new ChangePartyLootingEvent(party, owner, lootType));
            }
        }
    }*/

	return true;
}