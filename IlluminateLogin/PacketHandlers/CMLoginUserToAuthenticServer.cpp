#include "CMLoginUserToAuthenticServer.h"

bool CMLoginUserToAuthenticServer::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* inPacket = localObj.packet;

    Int8 index, zeroNumber, spacer1, spacer2;
    Int16 GPU;
    Int32 skipVal, RAM, ScreenW, ScreenH, cookie;
    Int64 pin, OperatingSystem, i64unk2;
    std::string strData, CPU, GPU;
    inPacket->Skip(62);        //skip(62); // auth token data, i presume we skip because we handle this on the nodejs server for token auth?
    *inPacket >> index;           //index = readC();
    skipVal = index * 8;
    *inPacket >> zeroNumber;           //zeroNumbers = readC();
    inPacket->Skip(skipVal);          //int skip = index * 8;
    *inPacket >> pin;    //pin = readQ();  //Long
    inPacket->Skip(160 - (skipVal + 8));      //skip((20 * 8) - (skip + 8));
    *inPacket >> cookie;           //cookie = readD(); // if login = 0; if comes from char list = tokenId;
    *inPacket >> OperatingSystem;            //readQ(); // 8 * 0x20
    *inPacket >> CPU;           //readS(42); // CPU name
    *inPacket >> spacer1;           //readC(); // 0 spacer? byte
    *inPacket >> RAM;           //readD(); // RAM amount //standard Int
    *inPacket >> GPU;           //readS(42); // GPU name
    *inPacket >> i64unk2;            //readQ(); // 0 unknown
    *inPacket >> spacer2;           //readC(); // 0 spacer? byte
    *inPacket >> ScreenW; //readD(); // screen width
    *inPacket >> ScreenH; //readD(); // screen height
    *inPacket >> GPU;     //readH(); // GPU name? stored in short

	IlluminatePacket* outPacket = new IlluminatePacket(Illuminate::SMLoginUserToAuthenticServer); //How do we handle our GetCookie? (GameServerRMI.GetCookie(client.Account)).Send(client);


	local.sock.sendPacket(outPacket);

	return true;
}