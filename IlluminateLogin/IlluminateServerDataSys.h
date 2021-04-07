#pragma once

#include "IlluminateDBDataSys.h"

class IlluminateServerDataSys
{
public:
	IlluminateServerDataSys();
	~IlluminateServerDataSys();

	bool initData();

	SharedPtr<CharDataInfo> getCharDataFromDBID(UInt32 dbID);
	SharedPtr<CharDataInfo> getCharDataFromTemplID(UInt32 templ);

private:

	bool initTemplates();
	bool initCharDataTable();

	IlluminateDBDataSys* dbDataSys;
	charTemplateFieldVec templateFieldVec;
	charTemplateVec templateDataVec;
	charDataVec charDataTableVec;

	enum class TEMPLATEFIELDCOL
	{
		ID = 0,
		NAME,
		TYPE
	};

	enum class TEMPLATEDATACOL
	{
		ID = 0,
		TID,
		FIELDID,
		FIELDVAL
	};

	enum class CHARDATACOL
	{
		ID = 0,
		TID,
		NAME,
		TYPE,
		RACE,
		GENDER,
		CLASS,
		LVL,
		STR,
		DEX,
		INT,
		CON,
		CHA,
		WIS,
		AC,
		MAXHP,
		MAXSP,
		MAXMP,
		CURHP,
		CURSP,
		CURMP,
		WALKSPEED,
		RUNSPEED,
		AR,
		DR,
		MAR,
		MDR,
		MINDMG,
		MAXDMG,
		ATKSPEED,
		RANGE,
		FIRERES,
		WATERRES,
		AIRRES,
		EARTHRES,
		MAGICRES,
		POISONRES,
		ICERES,
		THUNDERRES,
		MAGICHISTORY,
		MURDERPOINT,
		EXP,
		FIREMINDMG,
		FIREMAXDMG,
		WATERMINDMG,
		WATERMAXDMG,
		EARTHMINDMG,
		EARTHMAXDMG,
		AIRMINDMG,
		AIRMAXDMG,
		MAGICMINDMG,
		MAGICMAXDMG,
		POISONMINDMG,
		POISONMAXDMG,
		ICEMINDMG,
		ICEMAXDMG,
		THUNDERMINDMG,
		THUNDERMAXDMG,
		PHYSRESIS,
		SKILLBLOCK,
		SIGHT,
		BADGE1RANKPOINT,
		BADGE2RANKPOINT,
		BADGE3RANKPOINT,
		RANK,
		ITEMPOINT,
		GUILD,
		GUILDRANK,
		GUILDSCORE,
		LOSTEXP,
		WEAPON,
		ITEM1,
		ITEM2,
		ITEM3,
		ITEM4,
		ARMORHEAD,
		ARMORBODY,
		ARMORARM,
		ARMORHAND,
		ARMORLEG,
		ARMORFOOT,
		ARMORMANTLE,
		MONEY,
		GELDMIN,
		GELDMAX,
		DROPTID,
		SLOWPERCENT,
		SLOWTIME,
		FASTPERCENT,
		FASTTIME,
		PRODUCTSKINNAME,
		PRODUCTMEAT,
		PRODUCTMEATNAME,
		PRODUCTGARBAGE,
		PRODUCTGARBAGENAME,
		ATTRIBUTETYPE,
		NAMECOLOR,
		DROPRANK,
		DROPMEDITATION,
		SPIRITTYPE,
		LANDATTACHTYPE,
		TAMEABLE,
		RUNCORRECT,
		ATTACKCORRECT,
		SIEGECHARTYPE,
		RANGETYPE,
		STAMPOINT,
		PETTYPE,
		STARTSTAM,
		HEROICMINDMG,
		HEROICMAXDMG,
		HEROICDEFPT
	};
};