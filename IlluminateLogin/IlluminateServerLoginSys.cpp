#include "IlluminateServerLoginSys.h"

IlluminateServerLoginSys::IlluminateServerLoginSys()
{
	dbLoginSys = new IlluminateDBLoginSys();
}

IlluminateServerLoginSys::~IlluminateServerLoginSys()
{
	delete dbLoginSys;
}

bool IlluminateServerLoginSys::checkLogin(string username, string password)
{
	SharedPtr<RecordSet> rs = dbLoginSys->dbGetAccount(username, password);

	if (!rs)
		return false;

	if (rs->getTotalRowCount() == 0)
	{
		LOG("dbGetAccount() row count : 0", FATAL);
		return false;
	}

	return true;
}