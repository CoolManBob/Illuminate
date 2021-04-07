#include "IlluminateDatabase.h"

IlluminateDatabase::IlluminateDatabase()
{
	dbSessionPoolContainer = new SessionPoolContainer();
}

IlluminateDatabase::~IlluminateDatabase()
{
	delete dbSessionPoolContainer;
}

void IlluminateDatabase::createDBSession(std::string connectionString)
{
	//We currently only support MySQL sessions. POCO supports ODBC, and SQLite aswell, but it is unknown at this time if they will eventually be supported.
	dbSessionPool = new SessionPool("MySQL", connectionString);
	dbSessionPoolContainer->add(dbSessionPool);	
}

Session IlluminateDatabase::getDBSession(std::string sessionAlias)
{
	return dbSessionPoolContainer->get(sessionAlias);
}
