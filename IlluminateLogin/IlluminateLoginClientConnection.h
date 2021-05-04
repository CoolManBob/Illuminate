#pragma once
//#pragma pack(push,1)
#include <iostream>
#include <string>
#include <sstream>
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

#include "Poco/Exception.h"
using Poco::Exception;

#include "IlluminateLoginGlobal.h"
#include "IlluminateServerConnection.h"
#include "IlluminateLoginPacketHandler.h"
#include "IlluminateSocket.h"
#include "IlluminateBDOCrypt.h"

#include "IlluminateLocalSys.h"

const int maxReceiveBytes = 0x4100;

class IlluminateLoginClientConnection : public IlluminateServerConnection
{
public:
	IlluminateLoginClientConnection(const IlluminateSocket& socket, IlluminateLoginPacketHandler* packetHandler) : IlluminateServerConnection(socket, handler), handler(packetHandler), sock(socket)
	{
		cryptSession = new BDOCrypt;
		cryptSession->cryptoHandshake();
		sock.setCryptoSession(cryptSession);
		localSys = new IlluminateLocalSys();

		//Send SMSetFramework

	};
	virtual ~IlluminateLoginClientConnection() 
	{
		delete localSys;
		delete cryptSession;
		LOG("Client Disconnected!");
	};

	virtual void run()
	{
		//unsigned char tempBuf[maxReceiveBytes + 1] = { 0 };
		unsigned char* tempBuf = new unsigned char[maxReceiveBytes + 1];
		int numBytesRead = 1;
		for (; numBytesRead;)
		{
			try
			{
				numBytesRead = sock.receiveBytes(tempBuf, maxReceiveBytes);

				//Some security measures can be checked for here, mostly related to flooding.

				if (numBytesRead)
				{
					//1 - Packet Creation
					IlluminatePacket* packet = new IlluminatePacket(tempBuf, numBytesRead);
					delete[] tempBuf;

					//2 - Decrypt Packet
					bool decryptRes = sock.receivePacket(packet);
					if (!decryptRes)
					{
						LOG("ERROR Decrypting Packet", FATAL);
						continue;
					}

					//3 - Setup local information
					localInfo info(sock);
					info.packet = packet;

					/*stringstream outMsg;
					outMsg << "numBytesRead: " << numBytesRead << " ";
					outMsg << "PacketSize: " << packet->GetPacketSize() << " ";
					outMsg << "Opcode " << (int)packet->GetPacketType();
					LOG(outMsg.str());*/

					//4 - Handle Packet
					ActiveResult<bool> res = handler->packetHandler(info);
					res.wait();
					if (res.data())
					{
						/*stringstream successMsg;
						successMsg << "Opcode " << (int)packet->GetPacketType() << " handled successfully.";
						LOG(successMsg.str());*/
						delete packet;
					}
					else
					{
						/*stringstream errorMsg;
						errorMsg << "Error handling Opcode " << (int)packet->GetPacketType();
						LOG(errorMsg.str(), FATAL);*/
						delete packet;
					}
				}
			}
			catch (Exception&)
			{

			}
		}
	}
private:
	bool decryptPacket(IlluminatePacket * packet)
	{
		/*UInt32 realSize = 0;
		UInt8* packetData = packet->getBuffer();
		int isServerPacket = (packetData[0] == 0xA1) ? 1 : 0;
		
		if (packetData[0] == 0xD6 && packet->getSize() >= 16)
		{
			LOG("Unencrypted Packet");
			return true;
		}
		
		if ((packetData[0] != 0xB1 && packetData[0] != 0xA1) || packet->getSize() < 24)
			return false;

		packet->setSize(packet->getSize() - 8);
		memmove(packetData, packetData + 7, packet->getSize());

		for (int i = 0; i < (packet->getSize() >> 3); ++i)
			blowfish_decrypt((isServerPacket) ? cryptSession->serverCtx : cryptSession->clientCtx, (UInt32*)(packetData + i * (__int64)8), (UInt32*)(packetData + i * (__int64)8 + (__int64)4));

		if (packetData[0] != 0xD6)
			return false;

		return true;*/
		return false;
	}
	IlluminateLoginPacketHandler * handler;
	IlluminateSocket sock;
	BDOCrypt * cryptSession;

	//Internal data system
	IlluminateLocalSys * localSys;
};