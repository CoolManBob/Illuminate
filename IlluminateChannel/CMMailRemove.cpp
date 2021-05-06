#include "CMMailRemove.h"

bool CMMailRemove::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

	bool result;
	Int64 id;

	*inPacket >> id; //MailId in Database
	*inPacket >> result; //Was mail deleted? Yes or no

	/* Implement Logic here */

	/*
    public void runImpl() {
        final Player player = ((GameClient) this.getClient()).getPlayer();
        if (player != null) {
            final Mail mail = player.getMailBox().getMailMap().get(this.id);
            if (mail == null) {
                return;
            }
            if (mail.getItemId() > 0) {
                player.sendPacket(new SMNak(EStringTable.eErrNoDbInternalError, this.opCode));
                return;
            }
            if (player.getMailBox().removeMail(this.id) != null) {
                MailsDBCollection.getInstance().delete(this.id);
                player.sendPacket(new SMMailRemove(this.id, this.result));
            }
        }
    }*/
    IlluminatePacket* SMNakPkt = new IlluminatePacket(Illuminate::SMNak); //EStringTable.eErrNoDbInternalError 
                                                                          //Need to add EStringTable so client knows what LUA messages to load from Error
    return true;
}