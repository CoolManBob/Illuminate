#include "CMGetInstallationList.h"

bool CMGetInstallationList::processPacket(const localInfo& local)
{
    localInfo& localObj = const_cast<localInfo&>(local);
    IlluminatePacket* inPacket = localObj.packet;

    Int8 installationType;
    Int16 houseId;
    Int64 objectId, accountId;

    *inPacket >> objectId;
    *inPacket >> houseId;
    *inPacket >> accountId;
    *inPacket >> installationType;

    /* Implement Logic here */

    /*
    public void runImpl() {
        final Player player = this.getClient().getPlayer();
        if (player != null && player.isSpawned()) {
            switch (this.type) {
                case 5: {
                    HouseHold houseFixed = null;
                    final Player houseOwner = World.getInstance().getPlayerByAccount(this.accountId);
                    if (houseOwner != null) {
                        houseFixed = houseOwner.getHouseholdController().getHouseHold(this.objectId);
                    } else {
                        houseFixed = HouseHoldDBCollection.getInstance().load(this.objectId);
                    }
                    if (houseFixed != null) {
                        if (!houseFixed.getInstallations().isEmpty()) {
                            final ListSplitter<HouseInstallation> houseInstallationSplitter = new ListSplitter<>(houseFixed.getInstallations(), SMListFixedHouseInstallations.MAX_COUNT);
                            while (houseInstallationSplitter.hasNext()) {
                                player.sendPacket(new SMListFixedHouseInstallations(houseFixed, houseInstallationSplitter.getNext(), houseInstallationSplitter.isFirst() ? EPacketTaskType.Update : EPacketTaskType.Add));
                            }
                        }
                        player.getHouseVisit().setHouseId(this.houseId);
                        player.getHouseVisit().setHouseObjectId(this.objectId);
                        player.sendBroadcastItSelfPacket(new SMVisitHouse(player.getGameObjectId(), this.houseId, this.objectId));
                        break;
                    }
                    break;
                }
                default: {
                    player.getHouseVisit().setHouseId(0);
                    player.getHouseVisit().setHouseObjectId(0L);
                    break;
                }
            }
        }
    }*/

    return true;
}