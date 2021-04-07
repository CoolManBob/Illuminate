#include "IlluminateChannelServer.h"

IlluminateChannelServer::IlluminateChannelServer()
{
	handler = new IlluminateChannelPacketHandler();
	clientFactory = new IlluminateChannelClientFactory(handler);
	params = new TCPServerParams();
	channelServer = new TCPServer(clientFactory, 11008);
}

IlluminateChannelServer::~IlluminateChannelServer()
{

}

void IlluminateChannelServer::runServer()
{
	channelServer->start();

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

void IlluminateChannelServer::stopServer()
{
	channelServer->stop();
}