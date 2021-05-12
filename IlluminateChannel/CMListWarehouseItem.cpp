#include "CMListWarehouseItem.h"

bool CMListWarehouseItem::processPacket(const localInfo& local)
{
    localInfo& localObj = const_cast<localInfo&>(local);
    IlluminatePacket* inPacket = localObj.packet;
    
    Int8 storageType;
    Int16 townNodeId, i16unk1;
    Int32 i32unk1;
    Int64 guildId, i64unk1;
    
    *inPacket >> storageType;
    *inPacket >> townNodeId;
    *inPacket >> i32unk1;
    *inPacket >> i16unk1;
    *inPacket >> guildId;
    *inPacket >> i64unk1;

    /* Implement Logic here */

    /*
    public void runImpl() {
        if (getClient() == null)
            return;

        final Player player = ((GameClient) getClient()).getPlayer();

        // Guild Storage
        if (_storageType == 14) {
            final Guild guild = player.getGuild();
            if (_guildId > 0 && guild != null && _guildId == guild.getObjectId()) {
                final GuildWarehouse warehouse = guild.getGuildWarehouse();
                if (warehouse != null) {
                    final ListSplitter<Item> itemsSplitter = new ListSplitter(warehouse.getItemList(), 100);
                    while (itemsSplitter.hasNext()) {
                        player.sendPacket(new SMAddItemToWarehouse(itemsSplitter.getNext(), EItemStorageLocation.GuildWarehouse, _townNodeId, itemsSplitter.isFirst() ? EPacketTaskType.Add : EPacketTaskType.Update, 0, 0L));
                    }
                }
            }
        } else { // Others that are not implemented.
            if (player != null) {
                final Warehouse warehouse = player.getPlayerBag().getWarehouse(_townNodeId);
                if (warehouse != null) {
                    final ListSplitter<Item> itemsSplitter = new ListSplitter(warehouse.getItemList(), 100);
                    while (itemsSplitter.hasNext()) {
                        player.sendPacket(new SMAddItemToWarehouse(itemsSplitter.getNext(), EItemStorageLocation.Warehouse, _townNodeId, itemsSplitter.isFirst() ? EPacketTaskType.Add : EPacketTaskType.Update, 0, 0L));
                    }
                }
            }
        }
    }*/

    return true;
}