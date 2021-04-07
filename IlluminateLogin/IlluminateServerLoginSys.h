#pragma once

#include "IlluminateDBLoginSys.h"

class IlluminateServerLoginSys
{
public:
	IlluminateServerLoginSys();
	~IlluminateServerLoginSys();

	bool checkLogin(string username, string password);

private:
	IlluminateDBLoginSys* dbLoginSys;

	enum class ACCOUNTCOL
	{
		ACCTID,
		ACCTRNAME,
		ACCTPW
	};

};