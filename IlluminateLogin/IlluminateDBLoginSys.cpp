#include "IlluminateDBLoginSys.h"

IlluminateDBLoginSys::IlluminateDBLoginSys()
{

}

IlluminateDBLoginSys::~IlluminateDBLoginSys()
{

}

SharedPtr<RecordSet> IlluminateDBLoginSys::dbGetAccount(string username, string password)
{
	/*try
	{
		Session dbSession = dbInterface->getLoginDB();

		Statement acctInfo(dbSession);

		acctInfo << "SELECT * FROM account WHERE acctName = ? AND acctPW = ?", use(username), use(password), now;

		SharedPtr<RecordSet> rs = new RecordSet(acctInfo);

		return rs;
	}
	catch (const Poco::Exception& ex)
	{
		LOG(ex.displayText(), FATAL);
		return nullptr;
	}*/
}