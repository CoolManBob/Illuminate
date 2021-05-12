#include "CMSuggestGuildContract.h"

bool CMSuggestGuildContract::processPacket(const localInfo& local)
{
    localInfo& localObj = const_cast<localInfo&>(local);
    IlluminatePacket* inPacket = localObj.packet;

    Int16 contractPeriod;
    Int64 i64unk1, accountId, dailyPayment, leavePenaltyCost;


    *inPacket >> i64unk1; // Unknown
    *inPacket >> accountId; //Account ID of sending player
    *inPacket >> contractPeriod; //How long will the contract last
    *inPacket >> dailyPayment; //What is the contractee's daily guild pay
    *inPacket >> leavePenaltyCost; //How much silver does it cost the contractee to leave the guild before their contract has expired

    /* Implement Logic here */

    /*
    public void runImpl() {
        final Player player = this.getClient().getPlayer();
        if (player != null) {
            final Guild guild = player.getGuild();

            if (guild != null) {
                guild.onEvent(new SuggestGuildContractEvent(player, guild, _memberAccountId, _contractPeriod, _dailyPayment, _penaltyCost));
            }
        }
    }*/

    return true;
}