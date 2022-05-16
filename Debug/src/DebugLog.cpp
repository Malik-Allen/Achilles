#include "../include/DebugLog.h"


std::string DebugLog::outputLogFileName( "Output-Log.txt" );

void DebugLog::DebugLogInit()
{
	std::ofstream outputFile;
	outputFile.open( outputLogFileName, std::ios::out );	// We create the file using out just to make sure it is there and clears it
	outputFile.close();
}

std::string DebugLog::BuildTimeStamp()
{
	/*
		*	Code to obtain Date and Time stamps, adapted from:
		*	https://www.daniweb.com/programming/software-development/threads/177665/help-with-asctime-s-and-localtime-s
		*/
	char date[9];
	_strdate_s( date );
	char timestamp[9];
	_strtime_s( timestamp );

	/*[05/15/22|21:33:51]*/
	std::string dateTime;
	dateTime.append( "[" );
	dateTime.append( std::string( date ) );
	dateTime.append( "|" );
	dateTime.append( std::string( timestamp ) );
	dateTime.append( "]" );

	return dateTime;
}

std::string DebugLog::BuildFunctionSignature(const std::string& function, const int lineNumber )
{
	/*FunctionName(00):*/
	std::string signature;
	signature.append( function );
	signature.append( "(" );
	signature.append( std::to_string( lineNumber ) );
	signature.append( ")" );
	return signature;
}
