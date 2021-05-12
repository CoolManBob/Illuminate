#include "SMGetContentServiceInfo.h"

bool SMGetContentServiceInfo::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* outBound = localObj.packet;

	Int8 possibleClasses[12] = { 0,24,4,8,12,28,31,16,25,26,20,21 }; 
	Int8 i8unk1 = 4, i8unk2 = 0, i8unk3 = 0, i8unk4 = 32;
	Int8 DefaultCharacterSlot = 6, CharacterSlotLimit = 12; //Character Slots
	Int32 i32unk1 = 300000;
	Int32 i32unk2 = 0, i32unk3 = 0;
	Int32 MarketRefundForVP = 300000, MarketRefundForVPandPcBang = 350000; //Market place tax rates
	Int32 CharacterRemoveTimeCheckLevel = 1;
	Int64 LowLevelCharacterRemoveTime = 86400, CharacterRemoveTime = 86400, NameRemoveTime = 86400; //Character Deletion
	Int8 GuildWarType = 1, CanMakeGuild = 1; //Guild Management
	Int8 CanRegisterPearlItemOnMarket = 0;
	Int64 i64unk1 = 3000000, BiddingWaitTime = 100000;
	Int16 i16unk1 = 11;
	Int8 i8unk5 = 0;
	Int32 i32unk4 = 150;
	Int8 OpenedDesertPK = 1; //Desert PvP system for outlaws
	Int16 AccessibleRegionGroupKey[75] = { 1,2,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,31,33,34,36,37,38,39,40,41,42,43,44,45,46,51,52,53,54,55,56,58,61,62,63,64,101,102,103,104,105,106,107,108,109,110,111,112,202,203,204,205,206,207,208,209,210,211,212,213,214,215 };
	Int8 i8unk6 = 4;
	*outBound << i8unk1;
	*outBound << DefaultCharacterSlot;
	*outBound << CharacterSlotLimit;
	*outBound << i8unk2;
	*outBound << i8unk3;
	*outBound << i64unk1;
	*outBound << i32unk1;
	*outBound << i32unk2;
	*outBound << MarketRefundForVP;
	*outBound << MarketRefundForVPandPcBang;
	*outBound << BiddingWaitTime;
	*outBound << i8unk4 << possibleClasses[11]; //How do I select all from the array? also an extended int8 send for 32bytes
	*outBound << i32unk3;
	*outBound << CharacterRemoveTimeCheckLevel;
	*outBound << LowLevelCharacterRemoveTime;
	*outBound << CharacterRemoveTime;
	*outBound << NameRemoveTime;
	*outBound << GuildWarType;
	*outBound << CanMakeGuild;
	*outBound << i16unk1;
	*outBound << i8unk5;
	*outBound << i32unk4;
	*outBound << i8unk6 << AccessibleRegionGroupKey[74]; // Send each number in 4 bytes, not sure how to implement this?

	return true;
}