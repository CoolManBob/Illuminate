#pragma once

#include <vector>
#include <string>
using std::vector;
using std::string;

#include "Poco/Util/ServerApplication.h"

using namespace Poco::Util;

#include "IlluminateLoginServer.h"

class IlluminateLoginApp : public ServerApplication
{
public:
	IlluminateLoginApp() {};
	~IlluminateLoginApp() {};

protected:
	int main(const vector<string>&);
};