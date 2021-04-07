#include "IlluminateDBInterface.h"

#include <iostream>

IlluminateDBInterface::IlluminateDBInterface()
{
	Poco::Data::MySQL::Connector::registerConnector();

	database[	dbType::loginDB	] = new IlluminateDatabase();
	database[	dbType::worldDB	] = new IlluminateDatabase();
	database[	dbType::dataDB	] = new IlluminateDatabase();
}

IlluminateDBInterface::~IlluminateDBInterface()
{
	delete[] &database;
}

bool IlluminateDBInterface::createDatabaseConnection(dbType type, std::string connectionString)
{
	if (type > 2 || type < 0)
		return false;

	sessionNames[type] = "MySQL:///" + connectionString;

	database[type]->createDBSession(connectionString);

	return true;
}

Session IlluminateDBInterface::acquireDatabaseSession(dbType type)
{
	return database[type]->getDBSession(sessionNames[type]);
}

void IlluminateDBInterface::test()
{
	try {
		Session sess = database[0]->getDBSession(sessionNames[0]);

		Statement insert(sess);

		struct acct
		{
			int id;
			std::string name;
			std::string pw;
		};

		// insert some rows
		acct testacct =
		{
			2,
			"testinsert",
			"testinsert"
		};

		insert << "INSERT INTO account VALUES(?, ?, ?)",
			use(testacct.id),
			use(testacct.name),
			use(testacct.pw);

		insert.execute();
	}
	catch (const Poco::Exception& ex)
	{
		std::cout << ex.displayText() << std::endl;
	}
}