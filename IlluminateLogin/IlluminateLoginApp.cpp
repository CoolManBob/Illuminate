#include <iostream>
using std::cout;
using std::endl;

#include "IlluminateLoginGlobal.h"
#include "IlluminateLoginApp.h"
#include "IlluminateLoginServer.h"

IlluminateLog* IlluminateLogger;
IlluminateLoginConfig* loginConfig;
//IlluminatePacketInterface* pktInterface;
IlluminateDBInterface* dbInterface;

int IlluminateLoginApp::main(const vector<string>& args)
{
	/*cout << "|----------------------------------------------------------------|" << endl
		 <<  "|							ALEmu                                 |" << endl
		 <<  "|						  IlluminateLogin							      |" << endl
		 <<  "|                          v0.1								  |" << endl
		 <<  "|----------------------------------------------------------------|" << endl;*/

	IlluminateLogger = new IlluminateLog("IlluminateLogin.log", "IlluminateLogin");
	loginConfig = new IlluminateLoginConfig("IlluminateLogin.ini");
	//pktInterface = new IlluminatePacketInterface();
	dbInterface = new IlluminateDBInterface();

	cout << "ALEmu - IlluminateLogin v0.1" << endl;
	
	IlluminateLoginServer * loginServer = new IlluminateLoginServer();
	loginServer->runServer();
	
	LOG("HALT!", FATAL);

	loginServer->stopServer();

	waitForTerminationRequest();

	return Application::EXIT_OK;
}