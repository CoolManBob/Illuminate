#include "IlluminateLoginGlobal.h"
#include "IlluminateLoginServer.h"
#include "IlluminateLoginServerSystems.h"

IlluminateServerLoginSys* serverLoginSys;
IlluminateServerWorldListSys* serverListSys;
//IlluminateServerEncryptionSys* serverEncryptionSys;
//IlluminateServerDataSys* serverDataSys;

IlluminateLoginServer::IlluminateLoginServer()
{
	handler = new IlluminateLoginPacketHandler();
	clientFactory = new IlluminateLoginClientFactory(handler);
	params = new TCPServerParams();
}

IlluminateLoginServer::~IlluminateLoginServer()
{
	delete handler;
	delete clientFactory;
	delete loginServer;
}

void IlluminateLoginServer::runServer()
{
	std::string configLoad = loginConfig->loadConfig();
	LOG(configLoad);

	initDatabase();
	if (!initServerSystems())
	{
		LOG("ERROR: initServerSystems FAIL!", FATAL);
		return;
	}
	
	timeStamp.update(); //set timeStamp to current time.

	//create loginServer and start it
	loginServer = new TCPServer(clientFactory, loginConfig->getLoginPort());
	loginServer->start();
	LOG("Success: Server Start");

	updateServer();
}

void IlluminateLoginServer::stopServer()
{
	loginServer->stop();
	LOG("Success: Server Stop");
}

void IlluminateLoginServer::updateServer()
{
	while (true)
	{
		if (timeStamp.isElapsed(UPDATETIMER)) //Every 60 seconds we will handle any system updates.
		{
			LOG("updateServer", WARNING);
			
			if (!serverListSys->updateWorldList()) //Worldlist refresh error
				break;

			timeStamp.update();
		}
	}
}

void IlluminateLoginServer::initDatabase()
{
	//"host=localhost;port=3306;db=mydb;user=alice;password=s3cr3t;compress=true;auto-reconnect=true"
	std::string connectionStr;
	connectionStr = "host=" + loginConfig->getLoginDBAddress() + ";port=" + loginConfig->getLoginDBPort() + ";db=" + loginConfig->getLoginDB() + ";user=" + loginConfig->getLoginDBUser() + ";password=" + loginConfig->getLoginDBPass();

	dbInterface->createDatabaseConnection(IlluminateDBInterface::dbType::loginDB, connectionStr);

	connectionStr = "host=" + loginConfig->getWorldDBAddress() + ";port=" + loginConfig->getWorldDBPort() + ";db=" + loginConfig->getWorldDB() + ";user=" + loginConfig->getWorldDBUser() + ";password=" + loginConfig->getWorldDBPass();

	dbInterface->createDatabaseConnection(IlluminateDBInterface::dbType::worldDB, connectionStr);

	connectionStr = "host=" + loginConfig->getDataDBAddress() + ";port=" + loginConfig->getDataDBPort() + ";db=" + loginConfig->getDataDB() + ";user=" + loginConfig->getDataDBUser() + ";password=" + loginConfig->getDataDBPass();

	dbInterface->createDatabaseConnection(IlluminateDBInterface::dbType::dataDB, connectionStr);
}

bool IlluminateLoginServer::initServerSystems()
{
	serverLoginSys = new IlluminateServerLoginSys();
	serverListSys = new IlluminateServerWorldListSys();
	//serverEncryptionSys = new IlluminateServerEncryptionSys();

	if (!serverListSys->initWorldList())
	{
		LOG("ERROR: initWorldList FAIL!", FATAL);
		return false;
	}

	/*serverDataSys = new IlluminateServerDataSys();

	if (!serverDataSys->initData())
	{
		LOG("ERROR: initData FAIL!", FATAL);
		return false;
	}*/

	LOG("Success: ServerSys Init");
	return true;
}

