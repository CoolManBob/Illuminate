#include "IlluminateLoginConfig.h"

IlluminateLoginConfig::IlluminateLoginConfig()
{

}

IlluminateLoginConfig::IlluminateLoginConfig(std::string configPath)
{
	iniFile = new IniFileConfiguration(configPath);
}

IlluminateLoginConfig::~IlluminateLoginConfig()
{

}

std::string IlluminateLoginConfig::loadConfig()
{
	std::stringstream res("Success: Config Init");

	//Networking
	loginPort = getInt("IlluminateLogin.LoginServerPort");

	//Crypto
	cryptoKey = getString("IlluminateLogin.PacketCryptKey");
	if (cryptoKey.size() != 32)
	{
		res.clear();
		res << endl << "Wrong PacketCryptKey Size Got:" << cryptoKey.size() << " Expected: 32";
	}

	autogenCryptKey = getBool("IlluminateLogin.UseAutoGenCryptKey");

	//Deprecated
	worldAddress = getString("IlluminateLogin.WorldAddress");

	//LoginDB
	loginDBAddress = getString("IlluminateLogin.LoginDBAddress");
	loginDBPort = getString("IlluminateLogin.LoginDBPort");
	loginDBUser = getString("IlluminateLogin.LoginDBUser");
	loginDBPass = getString("IlluminateLogin.LoginDBPass");
	loginDB = getString("IlluminateLogin.LoginDB");

	//WorldDB
	worldDBAddress = getString("IlluminateLogin.WorldDBAddress");
	worldDBPort = getString("IlluminateLogin.WorldDBPort");
	worldDBUser = getString("IlluminateLogin.WorldDBUser");
	worldDBPass = getString("IlluminateLogin.WorldDBPass");
	worldDB = getString("IlluminateLogin.WorldDB");

	//DataDB
	dataDBAddress = getString("IlluminateLogin.DataDBAddress");
	dataDBPort = getString("IlluminateLogin.DataDBPort");
	dataDBUser = getString("IlluminateLogin.DataDBUser");
	dataDBPass = getString("IlluminateLogin.DataDBPass");
	dataDB = getString("IlluminateLogin.DataDB");

	return res.str();
}