#pragma once

#include <string>
using std::string;

#include <Poco/Logger.h>
#include <Poco/AutoPtr.h>
#include <Poco/FileChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/PatternFormatter.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/WindowsConsoleChannel.h>
#include <Poco/Message.h>
using Poco::Logger;
using Poco::AutoPtr;
using Poco::FormattingChannel;
using Poco::FileChannel;
using Poco::PatternFormatter;
using Poco::ColorConsoleChannel;
using Poco::WindowsColorConsoleChannel;
using Poco::Message;

class IlluminateLog
{

public:
	IlluminateLog();
	IlluminateLog(string logName, string channelName);
	IlluminateLog(string logName, int logChannel);
	IlluminateLog(string logName, int logChannel, int logPrio);
	~IlluminateLog() {};

	enum class LogPrio : int
	{
		LOG_INFO = 0,
		LOG_WARNING = 1,
		LOG_FATAL = 2
	};

	Logger& AcquireLogger(string logName) {};
	void test();
	void Log(string msg, LogPrio prio = LogPrio::LOG_INFO);

	void FLog(string msg); //Logs to file
	void CLog(string msg, LogPrio prio = LogPrio::LOG_INFO); //Logs to console

private:
	Logger* internalFileLogger;
	Logger* internalConsoleLogger;
};