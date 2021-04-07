#include "IlluminateDBDataSys.h"

IlluminateDBDataSys::IlluminateDBDataSys()
{

}

IlluminateDBDataSys::~IlluminateDBDataSys()
{

}

SharedPtr<RecordSet> IlluminateDBDataSys::dbGetTemplateFields()
{
	try
	{
		Session dbSession = dbInterface->getDataDB();

		Statement templateFields(dbSession);

		templateFields << "SELECT * FROM chartemplate_fields", now;

		SharedPtr<RecordSet> rs = new RecordSet(templateFields);

		return rs;
	}
	catch (const Poco::Exception& ex)
	{
		LOG(ex.displayText(), FATAL);
		return nullptr;
	}
}

SharedPtr<RecordSet> IlluminateDBDataSys::dbGetFullTemplateData()
{
	try
	{
		Session dbSession = dbInterface->getDataDB();

		Statement templateData(dbSession);

		templateData << "SELECT * FROM chartemplate_data", now;

		SharedPtr<RecordSet> rs = new RecordSet(templateData);

		return rs;
	}
	catch (const Poco::Exception& ex)
	{
		LOG(ex.displayText(), FATAL);
		return nullptr;
	}
}

SharedPtr<RecordSet> IlluminateDBDataSys::dbGetTemplateData(int tID)
{
	try
	{
		Session dbSession = dbInterface->getDataDB();

		Statement templateData(dbSession);

		templateData << "SELECT * FROM chartemplate_data WHERE template_id = ?", tID, now;

		SharedPtr<RecordSet> rs = new RecordSet(templateData);

		return rs;
	}
	catch (const Poco::Exception& ex)
	{
		LOG(ex.displayText(), FATAL);
		return nullptr;
	}
}

SharedPtr<RecordSet> IlluminateDBDataSys::dbGetCharDataTable()
{
	try
	{
		Session dbSession = dbInterface->getDataDB();

		Statement templateData(dbSession);

		templateData << "SELECT * FROM chardatatable", now;

		SharedPtr<RecordSet> rs = new RecordSet(templateData);

		return rs;
	}
	catch (const Poco::Exception& ex)
	{
		LOG(ex.displayText(), FATAL);
		return nullptr;
	}
}