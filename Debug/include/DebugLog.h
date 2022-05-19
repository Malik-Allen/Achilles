// MIT License, Copyright (c) 2022 Malik Allen

#ifndef DEBUGLOG_H
#define DEBUGLOG_H

#include <format>
#include <string>
#include <iostream>
#include <fstream>

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
	switch( logType )
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

#if DEBUG_MODE == 1	// ON
/* Creates brand new output file for logging */
#define DEBUG_INIT() ( DebugLog::DebugLogInit() )

/* Logs error to output log */
#define OUTPUT_FILE_LOG( LogType, Message, ... ) ( DebugLog::OutputFile_Log( LogType, Message, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__ ) )

/* Will print to console log */
#define CONSOLE_LOG( LogType, Message, ... ) ( DebugLog::Console_Log( LogType, Message, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__ ) )

/* Prints message to Output File and Console */
#define DEBUG_LOG( LogType, Message, ... ) ( OUTPUT_FILE_LOG(LogType, Message, __VA_ARGS__ ), CONSOLE_LOG(LogType, Message, __VA_ARGS__ ) )


#else	// OFF
/* Creates brand new output file for logging */
#define DEBUG_INIT()

/* Logs error to output log */
#define OUTPUT_FILE_LOG( LogType, Message )

/* Will print to console log */
#define CONSOLE_LOG( LogType, Message ) 

/* Prints message to Output File and Console */
#define DEBUG_LOG( LogType, Message, ... )


#endif


/*
*	Utility class for functionality around logging to console and output file
*/
class DebugLog
{

public:
	DebugLog() = delete;	// Static class, no constructor needed
	DebugLog( const DebugLog& ) = delete;
	DebugLog& operator=( const DebugLog& ) = delete;
	DebugLog( DebugLog&& ) = delete;
	DebugLog& operator=( DebugLog&& ) = delete;


	static void DebugLogInit();

	template<typename ... Args>
	static void OutputFile_Log( const LOG logType,
		const std::string& message,
		const std::string& fileName,
		const std::string& function,
		const int line,
		Args&& ... args )
	{
		std::ofstream outputFile;
		outputFile.open( outputLogFileName, std::ios::app | std::ios::out );

		/*[05/15/22|21:33:51][INFO]:	FunctionName(00):	Message {}*/
		std::string output;
		output.append( BuildTimeStamp() );
		output.append( "[" );
		output.append( ToString( logType ) );
		output.append( "]\t" );
		output.append( BuildFunctionSignature(function, line) );
		output.append( ":\t" );
		output.append( message );
		output.append( "\n" );

		outputFile << std::format( output, std::forward<Args>( args )... );

		outputFile.flush();
		outputFile.close();
	};


	template<typename ... Args>
	static void Console_Log( const LOG logType,
		const std::string& message,
		const std::string& fileName,
		const std::string& function,
		const int line,
		Args&& ... args )
	{
		/*[05/15/22|21:33:51][INFO]:	FunctionName(00):	Message {}*/
		std::string output;
		output.append( BuildTimeStamp() );
		output.append( "[" );
		output.append( ToString( logType ) );
		output.append( "]\t" );
		output.append( BuildFunctionSignature( function, line ) );
		output.append( ":\t" );
		output.append( message );
		output.append( "\n" );

		std::cout << std::format( output, std::forward<Args>( args )... );
	};

private:
	static std::string outputLogFileName;

	/* Returns a string in the format: [05/15/22|21:33:51]*/
	static std::string BuildTimeStamp();
	/* Returns a string in the format: FunctionName(00)*/
	static std::string BuildFunctionSignature( const std::string& function, const int lineNumber );
};



#endif	// DEBUGLOG_H
