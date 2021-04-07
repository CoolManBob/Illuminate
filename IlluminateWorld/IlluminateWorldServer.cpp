#include "IlluminateWorldServer.h"

IlluminateWorldServer::IlluminateWorldServer()
{
	handler = new IlluminateWorldPacketHandler();
	clientFactory = new IlluminateWorldClientFactory(handler);
	params = new TCPServerParams();
	worldServer = new TCPServer(clientFactory, 11008);
}

IlluminateWorldServer::~IlluminateWorldServer()
{

}

void IlluminateWorldServer::runServer()
{
	worldServer->start();

	/*int tickCount = 0;
	while (true)
	{
		if (tickCount == 500000000)
		{
			LOG("TICK COUNT 500000000");
			tickCount = 0;
		}

		tickCount++;
	}*/
}

void IlluminateWorldServer::stopServer()
{
	worldServer->stop();
}