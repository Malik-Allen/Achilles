#ifndef DEBUGLOG_H
#define DEBUGLOG_H

#include <string>
using namespace std;

enum class LOG : unsigned short
{
	NONE = 0,
	FATAL = 1,
	ERRORLOG = 2,
	WARNING = 3,
	TRACE = 4,
	INFO = 5
};

constexpr static const char* ToString( LOG logType )
{
	switch ( logType )
	{
	case LOG::NONE:			return "NONE";
	case LOG::FATAL:		return "FATAL ERROR";
	case LOG::ERRORLOG:		return "ERROR";
	case LOG::WARNING:		return "WARNING";
	case LOG::TRACE:		return "TRACE";
	case LOG::INFO:			return "INFO";
	}
}

#ifndef DEBUG_MODE 
#define DEBUG_MODE 1
#endif

#if DEBUG_MODE == 1



/* Creates brand new output file for logging */
#define DEBUG_INIT() ( DebugLog::DebugLogInit() )

/* Logs error to engine output log */
#define DEBUG_LOG( LogType, Message ) ( DebugLog::Log( LogType, Message, __FILE__, __FUNCTION__, __LINE__ ) )

/* Will print to console log */
#define CONSOLE_LOG( LogType, Message ) ( DebugLog::Console_Log( LogType, Message, __FILE__, __FUNCTION__, __LINE__ ) )

#else

/* Logs error to engine output log */
#define DEBUG_LOG( LogType, Message )

/* Will print to console log */
#define CONSOLE_LOG( LogType, Message ) 

/* Creates brand new output file for logging */
#define DEBUG_INIT()

#endif


// Static Debug Log Class
class DebugLog
{

public:

	DebugLog() = delete;	// Static class, no constructor needed
	DebugLog( const DebugLog& ) = delete;
	DebugLog& operator=( const DebugLog& ) = delete;
	DebugLog( DebugLog&& ) = delete;
	DebugLog& operator=( DebugLog&& ) = delete;

	static void DebugLogInit();
	static void Log( const LOG logType, const string& message, const string& fileName, const string& function, const int line );
	static void Console_Log( const LOG logType, const string& message, const string& fileName, const string& function, const int line );
	
private:

	static string outputLogFileName;


};



#endif	// DEBUGLOG_H
