#pragma once

#include "IlluminateLoginGlobal.h"
#include "IlluminateLoginTypes.h"

class IlluminateDBLoginSys
{
	friend class IlluminateServerLoginSys;
protected:
	IlluminateDBLoginSys();
	~IlluminateDBLoginSys();

	SharedPtr<RecordSet> dbGetAccount(std::string username, std::string password);

};