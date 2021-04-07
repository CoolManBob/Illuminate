#pragma once

#include "IlluminateLoginGlobal.h"
#include "IlluminateServerWorldListTypes.h"

class IlluminateDBWorldListSys
{
	friend class IlluminateServerWorldListSys;
protected:
	IlluminateDBWorldListSys();
	~IlluminateDBWorldListSys();

	SharedPtr<RecordSet> dbGetGroupInfo();
	SharedPtr<RecordSet> dbGetWorldInfo(int groupID);
};