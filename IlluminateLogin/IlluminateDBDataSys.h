#pragma once

#include "IlluminateLoginGlobal.h"
#include "IlluminateLoginTypes.h"

class IlluminateDBDataSys
{
	friend class IlluminateServerDataSys;
protected:
	IlluminateDBDataSys();
	~IlluminateDBDataSys();

	SharedPtr<RecordSet> dbGetTemplateFields();
	SharedPtr<RecordSet> dbGetFullTemplateData();
	SharedPtr<RecordSet> dbGetTemplateData(int tID);
	SharedPtr<RecordSet> dbGetCharDataTable();
};