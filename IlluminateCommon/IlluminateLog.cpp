#include "IlluminateLog.h"

IlluminateLog::IlluminateLog()
{
	internalConsoleLogger = nullptr;
	internalFileLogger = nullptr;

	FormattingChannel* pFCConsole = new FormattingChannel(new PatternFormatter("%p: %t"));
	pFCConsole->setChannel(new WindowsColorConsoleChannel);
	pFCConsole->open();

	FormattingChannel* pFCFile = new FormattingChannel(new PatternFormatter("%Y-%m-%d %H:%M:%S %p: %t"));
	pFCFile->setChannel(new FileChannel("Illuminate.log"));
	pFCFile->open();

	Logger& consoleLogger = Logger::create("IlluminateLogConsole", pFCConsole, Message::PRIO_TRACE);
	Logger& fileLogger = Logger::create("IlluminateLogFile", pFCFile, Message::PRIO_TRACE);

	internalConsoleLogger = &consoleLogger;
	internalFileLogger = &fileLogger;
}

IlluminateLog::IlluminateLog(string logName, string channelName)
{
	internalConsoleLogger = nullptr;
	internalFileLogger = nullptr;

	FormattingChannel* pFCConsole = new FormattingChannel(new PatternFormatter("%p: %t"));
	pFCConsole->setChannel(new WindowsColorConsoleChannel);
	pFCConsole->open();

	FormattingChannel* pFCFile = new FormattingChannel(new PatternFormatter("%Y-%m-%d %H:%M:%S %p: %t"));
	pFCFile->setChannel(new FileChannel(logName));
	pFCFile->open();

	Logger& consoleLogger = Logger::create(channelName + "Console", pFCConsole, Message::PRIO_TRACE);
	Logger& fileLogger = Logger::create(channelName + "File", pFCFile, Message::PRIO_TRACE);

	internalConsoleLogger = &consoleLogger;
	internalFileLogger = &fileLogger;
}

IlluminateLog::IlluminateLog(string logName, int logChannel)
{
	internalConsoleLogger = nullptr;
	internalFileLogger = nullptr;
}

IlluminateLog::IlluminateLog(string logName, int logChannel, int logPrio)
{
	internalConsoleLogger = nullptr;
	internalFileLogger = nullptr;
}

void IlluminateLog::test()
{
	internalConsoleLogger->trace("Trace Test Message");
	internalConsoleLogger->debug("Debug Test Message");
	internalConsoleLogger->information("Information Test Message");
	internalConsoleLogger->notice("Notice Test Message");
	internalConsoleLogger->warning("Warning Test Message");
	internalConsoleLogger->error("Error Test Message");
	internalConsoleLogger->critical("Critical Test Message");
	internalConsoleLogger->fatal("Fatal Test Message");
	internalFileLogger->trace("Trace Test Message");
	internalFileLogger->debug("Debug Test Message");
	internalFileLogger->information("Information Test Message");
	internalFileLogger->notice("Notice Test Message");
	internalFileLogger->warning("Warning Test Message");
	internalFileLogger->error("Error Test Message");
	internalFileLogger->critical("Critical Test Message");
	internalFileLogger->fatal("Fatal Test Message");
}

void IlluminateLog::Log(string msg, LogPrio prio)
{
	switch (prio)
	{
		case LogPrio::LOG_FATAL:
		{
			internalConsoleLogger->fatal(msg);
			internalFileLogger->fatal(msg);
		} break;
		case LogPrio::LOG_WARNING:
		{
			internalConsoleLogger->warning(msg);
			internalFileLogger->warning(msg);
		} break;
		case LogPrio::LOG_INFO:
		{
			internalConsoleLogger->information(msg);
			internalFileLogger->information(msg);
		} break;
		default:
		{
			internalConsoleLogger->error(msg);
			internalFileLogger->error(msg);
		} break;
	}
}

void IlluminateLog::FLog(string msg)
{
	internalFileLogger->information(msg);
}

void IlluminateLog::CLog(string msg, LogPrio prio)
{
	switch (prio)
	{
	case LogPrio::LOG_FATAL:		internalConsoleLogger->fatal(msg); break;
	case LogPrio::LOG_WARNING:		internalConsoleLogger->warning(msg); break;
	case LogPrio::LOG_INFO:			internalConsoleLogger->information(msg); break;
	default:						internalConsoleLogger->error(msg); break;
	}
}