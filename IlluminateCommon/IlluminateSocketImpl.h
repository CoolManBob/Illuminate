#pragma once

#include "Poco/Net/StreamSocketImpl.h"

using namespace Poco::Net;

#include "IlluminateSocket.h"

class IlluminateSocketImpl : public StreamSocketImpl
{
public:
	IlluminateSocketImpl() {};
	virtual ~IlluminateSocketImpl() {};
};