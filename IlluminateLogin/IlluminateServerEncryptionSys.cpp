#include "Poco/RandomStream.h"
#include <iostream>

using Poco::RandomInputStream;

#include "IlluminateServerEncryptionSys.h"

IlluminateServerEncryptionSys::IlluminateServerEncryptionSys()
{

}

IlluminateServerEncryptionSys::~IlluminateServerEncryptionSys()
{

}

std::string IlluminateServerEncryptionSys::getCryptKey()
{
	//KeyGen
	RandomInputStream ri;
	std::string rs;
	ri >> rs;
	rs.resize(32);
	return rs;
}