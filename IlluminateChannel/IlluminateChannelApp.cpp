#include <iostream>
using std::cout;
using std::endl;

#include "IlluminateChannelGlobal.h"
#include "IlluminateChannelApp.h"
#include "IlluminateChannelServer.h"

IlluminateLog* IlluminateLogger;
IlluminatePacketInterface* pktInterface;

int IlluminateChannelApp::main(const vector<string>& args)
{
	/*cout << "|----------------------------------------------------------------|" << endl
	<<  "|							Illuminate                                |" << endl
	<<  "|						  IlluminateChannel							      |" << endl
	<<  "|                          v0.1								  |" << endl
	<<  "|----------------------------------------------------------------|" << endl;*/

	IlluminateLogger = new IlluminateLog("IlluminateChannel.log", "IlluminateChannel");
	pktInterface = new IlluminatePacketInterface();

	cout << "IlluminateEmu - IlluminateChannel v0.1" << endl;
	IlluminateChannelServer * ChannelServer = new IlluminateChannelServer();
	ChannelServer->runServer();

	LOG("Server Start");

	waitForTerminationRequest();

	LOG("Server Stopped");

	ChannelServer->stopServer();

	return Application::EXIT_OK;
}