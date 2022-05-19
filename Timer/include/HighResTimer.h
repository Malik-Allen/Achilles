// MIT License, Copyright (c) 2022 Malik Allen

#pragma once

#include <Windows.h>

#define MILLISECONDS_TO_SECONDS (1 / 1000.0f)
#define MICROSECONDS_TO_SECONDS (1 / 1000000.0f)
#define SECONDS_TO_MILLISECONDS (1000 / 1)
#define SECONDS_TO_MICROSECONDS (1000000 / 1)

/*
*  
*/
class HighResTimer
{
	HighResTimer( const HighResTimer& ) = delete;
	HighResTimer& operator=( const HighResTimer& ) = delete;
	HighResTimer( HighResTimer&& ) = delete;
	HighResTimer& operator=( HighResTimer&& ) = delete;
public:
	HighResTimer();
	virtual ~HighResTimer() = default;

	unsigned int GetCurrentTimeInMicroSeconds();
	unsigned int GetCurrentTimeInMilliSeconds();

private:
	LARGE_INTEGER frequency;	// 'Ticks-per-second' 
	LARGE_INTEGER currentTicks;

	//**IMPORTANT: LARGE_INTEGER is a union that has member value called 'QuadPart' which stores a 64bit signed int
		// 'QuadPart' should be used for a compiler with support for 64-bit integers, where as 'HighPart' and 'LowPart' should be used otherwise.

};