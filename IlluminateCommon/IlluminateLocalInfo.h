#pragma once

#define _localSock local.sock
#define _localPkt local.packet
#define _localSys local.localSys

#include "IlluminatePacket.h"
#include "IlluminateSocket.h"
#include "IlluminateLocalSys.h"

struct localInfo
{
	localInfo(IlluminateSocket& socket) : sock(socket), packet(nullptr), localSys(nullptr) {};
	localInfo(IlluminateLocalSys* local, IlluminateSocket& socket) : localSys(local), sock(socket), packet(nullptr) {};
	IlluminateLocalSys* localSys;
	IlluminatePacket* packet;
	IlluminateSocket& sock;
};