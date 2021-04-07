#pragma once

#include <vector>
#include <string>
using std::vector;
using std::string;

#include "Poco/Util/ServerApplication.h"

using namespace Poco::Util;

#include "IlluminateWorldServer.h"

class IlluminateWorldApp : public ServerApplication
{
public:
	IlluminateWorldApp() {};
	~IlluminateWorldApp() {};

protected:
	int main(const vector<string>&);
};