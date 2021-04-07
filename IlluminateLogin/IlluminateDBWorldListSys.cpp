#include "IlluminateDBWorldListSys.h"

IlluminateDBWorldListSys::IlluminateDBWorldListSys()
{

}

IlluminateDBWorldListSys::~IlluminateDBWorldListSys()
{

}

SharedPtr<RecordSet> IlluminateDBWorldListSys::dbGetGroupInfo()
{
	try 
	{
		Session dbSession = dbInterface->getLoginDB();

		Statement groupInfo(dbSession);

		groupInfo << "SELECT * FROM worldgroup", now;

		SharedPtr<RecordSet> rs = new RecordSet(groupInfo);

		return rs;
	}
	catch (const Poco::Exception& ex)
	{
		LOG(ex.displayText(), FATAL);
		return nullptr;
	}
}

SharedPtr<RecordSet> IlluminateDBWorldListSys::dbGetWorldInfo(int groupID)
{
	try
	{
		Session dbSession = dbInterface->getLoginDB();

		Statement worldInfo(dbSession);

		worldInfo << "SELECT * FROM worldlist WHERE groupID = ?", use(groupID), now;

		SharedPtr<RecordSet> rs = new RecordSet(worldInfo);
		return rs;
	}
	catch (const Poco::Exception& ex)
	{
		LOG(ex.displayText(), FATAL);
		return nullptr;
	}
}