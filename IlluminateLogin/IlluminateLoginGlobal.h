#pragma once
//File used for global variables if any
#include <iostream>
#include <string>
#include <sstream>
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

#include <Poco/SharedPtr.h>
using Poco::SharedPtr;

#include <Poco/Data/Statement.h>
using Poco::Data::Keywords::now;
using Poco::Data::Keywords::use;
using Poco::Data::Keywords::into;
using Poco::Data::Keywords::bind;

#include <Poco/Timestamp.h>
using Poco::Timestamp;

#include <Poco/HMACEngine.h>
#include <Poco/SHA2Engine.h>
using Poco::HMACEngine;
using Poco::SHA2Engine;


#include "IlluminateLog.h"
#include "IlluminateLoginConfig.h"
#include "IlluminatePacketInterface.h"
#include "IlluminateDBInterface.h"

#define LOG IlluminateLogger->Log
#define FATAL IlluminateLog::LogPrio::LOG_FATAL
#define WARNING IlluminateLog::LogPrio::LOG_WARNING
#define INFO IlluminateLog::LogPrio::LOG_INFO

#define COLIDX(x) static_cast<int>(x)

//Global Interfaces
extern IlluminateLog* IlluminateLogger;
extern IlluminateLoginConfig* loginConfig;
extern IlluminatePacketInterface* pktInterface;
extern IlluminateDBInterface* dbInterface;
