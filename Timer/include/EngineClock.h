// MIT License, Copyright (c) 2022 Malik Allen

#pragma once

#include "HighResTimer.h"

/*
* 
*/
class EngineClock : public HighResTimer
{
	EngineClock( const EngineClock& ) = delete;
	EngineClock& operator=( const EngineClock& ) = delete;
	EngineClock( EngineClock&& ) = delete;
	EngineClock& operator=( EngineClock&& ) = delete;

public:
	EngineClock();
	~EngineClock();

	unsigned int GetFPS();
	void SetFPS( unsigned int fps );

	void Reset();
	void UpdateFrameTicks();
	float GetDeltaTime() const;
	unsigned int GetSleepTime( const unsigned int fps );
	float GetCurrentTicks() const;

private:
	unsigned int m_prevTicks, m_currentTicks, m_fps;

};
