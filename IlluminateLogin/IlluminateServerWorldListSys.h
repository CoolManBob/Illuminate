#pragma once

#include "IlluminateLoginGlobal.h"
#include "IlluminateLoginTypes.h"
#include "IlluminateDBWorldListSys.h"

class IlluminateServerWorldListSys
{
public:
	IlluminateServerWorldListSys();
	~IlluminateServerWorldListSys();

	bool initWorldList();

	string buildWorldInfoStr();

	string getWorldAddress(string worldName);

	bool updateWorldList();

	enum SERVERSTATUS
	{
		CLOSED = 0,
		LOWPOP,
		MEDPOP,
		HIGHPOP,
		FULLPOP,
		EXCESS,
	};

private:
	IlluminateDBWorldListSys* dbWorldList;
	worldListGroupVec worldList;

	bool getGroupInfo();
	bool getWorldInfo();

	//DB
	enum class GROUPCOL
	{
		ID = 0,
		NAME
	};

	enum class WORLDCOL
	{
		ID = 0,
		GROUPID,
		NAME,
		ADDRESS,
		STATUS,
		FLAG
	};
};