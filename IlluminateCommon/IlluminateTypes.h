#pragma once

#include <Poco/Foundation.h>

using Poco::Int8;
using Poco::UInt8;
using Poco::Int16;
using Poco::UInt16;
using Poco::Int32;
using Poco::UInt32;
using Poco::Int64;
using Poco::UInt64;

namespace Illuminate
{
	const int IlluminateTypeSize[16] = { 1, 1, 1, 2, 2, 4, 4, 8, 8, 4, 12, 64, 8, 0, 6, 2 };

	enum IlluminateType
	{
		CHAR, // 0
		INT8, // 1
		UINT8, // 2
		INT16, // 3
		UINT16, // 4
		INT32, // 5
		UINT32, // 6
		INT64, // 7
		UINT64, // 8
		FLOAT, // 9
		VEC3F, // 0xa (10)
		MATRIX, // 0xb (11)
		PACKET, // 0xc (12)
		MEMORY_BLOCK, // 0xd (13)
		POS_BASEMETER, // 0xe (14)
		WCHAR, // 0xf (15)
		MAX, // 0x10 (16)
	};

	struct IlluminateVec3F
	{
		IlluminateVec3F() { x = 0; y = 0; z = 0; }
		IlluminateVec3F(float inX, float inY, float inZ) { x = inX; y = inY; z = inZ; }
		float x;
		float y;
		float z;
	};

	struct IlluminatePktField
	{
		IlluminatePktField() { FieldType = 0; FieldSize = 0; }
		UInt8 FieldType;
		UInt32 FieldSize;
	};

	//Main Packet Types
	enum IlluminatePacketType
	{
		Illuminate_SYSTEM_PACKET_TYPE = 0,
		AGPMCONFIG_PACKET_TYPE = 1,
		AGPMCHARACTER_PACKET_TYPE = 2,
		AGSMCHARMANAGER_PACKET_TYPE = 3,
		AGPMITEM_PACKET_TYPE = 4,
		AGPMLOGIN_PACKET_TYPE = 0x0D,
		AGPMTIMER_PACKET_TYPE = 0x11,
		AGPMADMIN_PACKET_TYPE = 0x12,
		AGPMUISTATUS_PACKET_TYPE = 0x14,
		AGPMWORLD_PACKET_TYPE = 0x18,
		AGPMEVENT_MANAGER = 0x3C,
		AGPMOPTIMIZEDCHARMOVE_PACKET_TYPE = 0x40,
		AGPMOPTIMIZEDCHARACTION_PACKET_TYPE = 0x41,
		AGPMOPTIMIZEDVIEW_PACKET_TYPE = 0x42,
		AGPMSTARTUPENCRYPTION_PACKET_TYPE = 0x48,
		AGPM_TITLE_PACKET_TYPE = 0x60,
	};

	//Naming Convention - SYSTEM_PACKETTYPE_2NDTYPE
	//These are used to identify Mini Packets (Packet's within main packets)
	enum IlluminateMiniPacketType
	{
		AGPMLOGIN_SERVER_ADDR = 100,
		AGPMLOGIN_CHAR_INFO,
		AGPMLOGIN_SERVER_INFO,
		AGPMLOGIN_VERSION_INFO,
		AGPMLOGIN_COMPEN_INFO,
		AGPMCHAR_MOVE,
		AGPMCHAR_SKILL,
		AGPMCHAR_FACTORS,
		AGPMCHAR_FACTOR_STATUS,
		AGPMCHAR_FACTOR_TYPE,
		AGPMCHAR_FACTOR_POINT,
		AGPMCHAR_FACTOR_POINTMAX,
		AGPMCHAR_FACTOR_RECOVERY,
		AGPMCHAR_FACTOR_ATTRIBUTE,
		AGPMCHAR_FACTOR_DMG,
		AGPMCHAR_FACTOR_DEFENSE,
		AGPMCHAR_FACTOR_ATTACK,
		AGPMCHAR_FACTOR_ITEM,
		AGPMCHAR_FACTOR_DIRT,
		AGPMCHAR_FACTOR_PRICE,
		AGPMOPTIMIZEDPACKET_VIEW,
		AGPMOPTIMIZEDPACKET_ITEMVIEW,
	};

	/*enum ePacketType
	{
		Illuminate_SYSTEM_PACKET_TYPE = 0,
		AGPMCONFIG_PACKET_TYPE = 1,
		AGPMCHARACTER_PACKET_TYPE = 2,
		AGCMCHAR_PACKET_TYPE = 3,
		AGSMCHARMANAGER_PACKET_TYPE = 3
		AGPMITEM_PACKET_TYPE = 4
		AGPMSKILL_PACKET_TYPE = 5
		AGPMSHRINE_PACKET_TYPE = 6
		AGPMPRIVATETRADE_PACKET_TYPE = 7
		AGPMPARTY_PACKET_TYPE = 8
		AGCMPARTY_PACKET_TYPE = 9
		AGSMPARTY_PACKET_TYPE = 9
		AGPMRECRUIT_PACKET_TYPE = 0Ah
		AGPMAUCTION_PACKET_TYPE = 0Bh
		AGPMSYSTEMINFO_PACKET_TYPE = 0Ch
		AGPMLOGIN_PACKET_TYPE = 0Dh
		AGPMOBJECT_PACKET_TYPE = 0Eh
		AGPMCHATTING_PACKET_TYPE = 0Fh
		AGPMAI_PACKET_TYPE = 10h
		AGPMTIMER_PACKET_TYPE = 11h
		AGPMADMIN_PACKET_TYPE = 12h
		AGPMQUEST_PACKET_TYPE = 13h
		AGPMUISTATUS_PACKET_TYPE = 14h
		AGPMGUILD_PACKET_TYPE = 15h
		AGPMITEMCONVERT_PACKET_TYPE = 16h
		AGPMPRODUCT_PACKET_TYPE = 17h
		AGPMWORLD_PACKET_TYPE = 18h
		AGPMCASPER_PACKET_TYPE = 19h
		AGSMSERVER_PACKET_TYPE = 1Ah
		AGCMCONNECTMANAGER_PACKET_TYPE = 1Bh
		AGSMCHARACTER_PACKET_TYPE = 1Bh
		AGSMACCOUNT_PACKET_TYPE = 1Ch
		AGSMRECRUIT_PACKET_TYPE = 1Dh
		AGSMAUCTION_PACKET_TYPE = 1Eh
		AGSMITEM_PACKET_TYPE = 1Fh
		AGSMSKILL_PACKET_TYPE = 20h
		AGSMDEATH_PACKET_TYPE = 21h
		AGSMLOGIN_PACKET_TYPE = 22h
		AGSMZONING_PACKET_TYPE = 23h
		AGSMADMIN_PACKET_TYPE = 24h
		AGSMRELAY_PACKET_TYPE = 25h
		AGSMITEMLOG_PACKET_TYPE = 26h
		AGSMLOG_PACKET_TYPE = 27h
		AGSMGUILD_PACKET_TYPE = 28h
		AGPMPARTYITEM_PACKET_TYPE = 29h
		AGPMREMISSION_PACKET_TYPE = 2Ah
		AGPMBUDDY_PACKET_TYPE = 2Bh
		AGPMCHANNEL_PACKET_TYPE = 2Ch
		AGPMMAILBOX_PACKET_TYPE = 2Dh
		AGPMCASHMALL_PACKET_TYPE = 2Eh
		AGPMRETURNTOLOGIN_PACKET_TYPE = 2Fh
		AGPMEVENT_NATURE_PACKET_TYPE = 30h
		AGPMEVENT_TELEPORT_PACKET_TYPE = 31h
		AGPMEVENT_NPCTRADE_PACKET_TYPE = 32h
		AGPMEVENT_ITEMREPAIR_PACKET_TYPE = 34h
		AGPMEVENT_MASTERY_SPECIALIZE_PACKET_TYPE = 35h
		AGPMEVENT_BANK_PACKET_TYPE = 36h
		AGPMEVENT_NPCDIALOG_PACKET_TYPE = 37h
		AGPMEVENT_ITEMCONVERT_PACKET_TYPE = 38h
		AGPMEVENT_GUILD_PACKET_TYPE = 39h
		AGPMEVENT_PRODUCT_PACKET_TYPE = 3Ah
		AGPMEVENT_SKILLMASTER_PACKET_TYPE = 3Bh
		AGPMEVENT_MANAGER = 3Ch
		AGPMEVENT_QUEST_PACKET_TYPE = 3Eh
		AGPMEVENT_REFINERY_PACKET_TYPE = 3Fh
		AGPMOPTIMIZEDCHARMOVE_PACKET_TYPE = 40h
		AGPMOPTIMIZEDCHARACTION_PACKET_TYPE = 41h
		AGPMOPTIMIZEDVIEW_PACKET_TYPE = 42h
		AGPMEVENT_CHARCUSTOMIZE_PACKET_TYPE = 43h
		AGPMSYSTEMMESSAGE_PACKET_TYPE = 44h
		AGPMSCRPIT_PACKET_TYPE = 45h
		AGPMWANTEDCRIMINAL_PACKET_TYPE = 46h
		AGPMNATUREEFFECT_PACKET_TYPE = 47h
		AGPMSTARTUPENCRYPTION_PACKET_TYPE = 48h
		AGPMSIEGEWAR_PACKET_TYPE = 49h
		AGPMPVP_PACKET_TYPE = 4Ah
		AGPMREFINERY_PACKET_TYPE = 4Bh
		AGPMAREACHATTING_PACKET_TYPE = 4Ch
		AGPMRIDE_PACKET_TYPE = 4Dh
		AGPMBILLINFO_PACKET_TYPE = 4Eh
		AGPMSUMMONS_PACKET_TYPE = 4Fh
		AGPMEVENT_SIEGEWAR_NPC_PACKET_TYPE = 50h
		AGSMGLOBALCHATTING_PACKET_TYPE = 51h
		AGPMSEARCH_PACKET_TYPE = 52h
		AGPMTAX_PACKET_TYPE = 53h
		AGPMGUILDWAREHOUSE_PACKET_TYPE = 54h
		AGPMARCHLORD_PACKET_TYPE = 55h
		AGPMGAMBLE_PACKET_TYPE = 56h
		AGPMEVENT_GACHA_PACKET_TYPE = 57h
		AGPM_BATTLEGROUND_PACKET_TYPE = 58h
		AGPM_EPICZONE_PACKET_TYPE = 59h
		AGPM_TITLE_PACKET_TYPE = 60h
		}*/

}