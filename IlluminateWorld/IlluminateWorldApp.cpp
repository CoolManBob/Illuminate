#include <iostream>
using std::cout;
using std::endl;

#include "IlluminateWorldGlobal.h"
#include "IlluminateWorldApp.h"
#include "IlluminateWorldServer.h"

IlluminateLog* IlluminateLogger;
IlluminatePacketInterface* pktInterface;

int IlluminateWorldApp::main(const vector<string>& args)
{
	/*cout << "|----------------------------------------------------------------|" << endl
	<<  "|						   IlluminateEmu                                 |" << endl
	<<  "|						  IlluminateWorld							      |" << endl
	<<  "|                          v0.1								  |" << endl
	<<  "|----------------------------------------------------------------|" << endl;*/

	IlluminateLogger = new IlluminateLog("IlluminateWorld.log", "IlluminateWorld");
	pktInterface = new IlluminatePacketInterface();

	cout << "IlluminateEmu - IlluminateWorld v0.1" << endl;
	IlluminateWorldServer * worldServer = new IlluminateWorldServer();
	worldServer->runServer();

	LOG("Server Start");

	waitForTerminationRequest();

	LOG("Server Stopped");

	worldServer->stopServer();

	return Application::EXIT_OK;
}