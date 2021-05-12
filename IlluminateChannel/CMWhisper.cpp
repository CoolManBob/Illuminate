#include "CMWhisper.h"

bool CMWhisper::processPacket(const localInfo& local)
{
    localInfo& localObj = const_cast<localInfo&>(local);
    IlluminatePacket* inPacket = localObj.packet;

    Int8 whisperType;
    std::string Name, Message;
    Name.reserve(62);

    *inPacket >> whisperType;
    *inPacket >> Name;
    *inPacket >> Message;

    /* Implement Logic here */

    /*
    public void runImpl() {
        final Player player = this.getClient().getPlayer();
        if (player != null) {
            final Player target = _whisperType > 0
                    ? World.getInstance().getPlayerByFamily(_name)
                    : World.getInstance().getPlayer(_name);
            if (target == null) {
                player.sendPacket(new SMCantFindWhisperPlayer(_name));
                return;
            }
            ChatService.getInstance().sendPrivateMessage(player, target, _msg);
        }
    }*/

    return true;
}