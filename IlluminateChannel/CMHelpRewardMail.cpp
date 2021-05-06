#include "CMHelpRewardMail.h"

bool CMHelpRewardMail::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	Int8 storageType, slotIndex;
	std::string strData, senderName, mailSubject, mailMessage;
	senderName.reserve(62);
	mailSubject.reserve(202);
	mailMessage.reserve(602);

	*inPacket >> storageType; //Get mail from DB
	*inPacket >> slotIndex; //buffer & 0xFF //Get attached item
	*inPacket >> senderName; //Name of who sent the mail
	*inPacket >> mailSubject; //Subject of the mail
	*inPacket >> mailMessage; //Text of the mail


	/* Implement Logic here */

	/*
	public void runImpl() {
		final Player player = ((GameClient) this.getClient()).getPlayer();
		if (player != null) {
			player.getPlayerBag().onEvent(new RewardMailItemEvent(player, this.storageType, this.slotIndex, this.name, this.mailSubject, this.mailMessage));
		}
	}*/

	return true;
}