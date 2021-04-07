#pragma once

#include <vector>
#include <string>
using std::vector;
using std::string;

#include "Poco/Util/ServerApplication.h"

using namespace Poco::Util;

#include "IlluminateChannelServer.h"

class IlluminateChannelApp : public ServerApplication
{
public:
	IlluminateChannelApp() {};
	~IlluminateChannelApp() {};

protected:
	int main(const vector<string>&);
};