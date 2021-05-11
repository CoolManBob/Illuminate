#include "CMChat.h"

bool CMChat::processPacket(const localInfo& local)
{
    localInfo& localObj = const_cast<localInfo&>(local);
    IlluminatePacket* inPacket = localObj.packet;

    Int8 type, i8unk1, i8unk2;
    Int32 slotIndex, i32unk1;
    std::string strData, Message;

    *inPacket >> type;
    *inPacket >> i8unk1;
    *inPacket >> slotIndex;
    *inPacket >> i32unk1;
    *inPacket >> i8unk2;
    *inPacket >> Message;

    /* Implement Logic here */

    /*
    public void runImpl() {
        final Player player = this.getClient().getPlayer();
        if (player != null) {
            final EChatType chatType = EChatType.valueOf(this.type);
            if (chatType != null)
                ChatService.getInstance().sendMessage(player, this.msg, chatType, EChatNoticeType.Normal, this.slotIndex, 0, 0, null, null, this.getClass());
        }
    }*/

    return true;
}