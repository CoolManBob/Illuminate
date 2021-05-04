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

#include "IlluminateLog.h"

#define LOG IlluminateLogger->Log
#define FATAL IlluminateLog::LogPrio::LOG_FATAL
#define WARNING IlluminateLog::LogPrio::LOG_WARNING
#define INFO IlluminateLog::LogPrio::LOG_INFO

//namespace IlluminateGlobal
//{
extern IlluminateLog* IlluminateLogger;
//}