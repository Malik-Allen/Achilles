#include "../include/DebugLog.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include <stdio.h>


string DebugLog::outputLogFileName( "Output-Log.txt" );

void DebugLog::DebugLogInit()
{
	ofstream outputFile;
	outputFile.open( outputLogFileName, ios::out );	// We create the file using out just to make sure it is there and clears it
	outputFile.close();
}

void DebugLog::Log( const LOG logType, const string& message, const string& fileName, const string& function, const int line )
{
	// Note on @param fileName:
		// FileName is currently not in use, 
		// it ends up causing a lot of clutter in logs, 
		// Once I am able to use a relative rather than a direct path, it will be reconsidered 

	ofstream outputFile;
	outputFile.open( outputLogFileName, ios::app | ios::out );

	/*
		Code to obtain Date and Time stamps, adapted from:
		https://www.daniweb.com/programming/software-development/threads/177665/help-with-asctime-s-and-localtime-s
	*/
	char date[9];
	_strdate_s( date );
	char timestamp[9];
	_strtime_s( timestamp );


	outputFile << "[" << date << "|" << timestamp << "]" << "[" << ToString( logType ) << "]:\t" << function << "(" << line << "):\t" << message << endl;
	

	outputFile.flush();
	outputFile.close();
}

void DebugLog::Console_Log( const LOG logType, const string & message, const string & fileName, const string& function, const int line )
{
	/*
		Code to obtain Date and Time stamps, adapted from:
		https://www.daniweb.com/programming/software-development/threads/177665/help-with-asctime-s-and-localtime-s
	*/
	char date[9];
	_strdate_s( date );
	char timestamp[9];
	_strtime_s( timestamp );

	
	cout << "[" << date << "|" << timestamp << "]" << "[" << ToString( logType ) << "]:\t" << function << "(" << line << "):\t" << message << endl;
	
}
