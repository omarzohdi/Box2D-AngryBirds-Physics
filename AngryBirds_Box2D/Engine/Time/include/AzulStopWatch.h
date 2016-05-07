/*
 *  AZULSTOPWATCH.h
 */

#ifndef AZUL_STOP_WATCH_H
#define AZUL_STOP_WATCH_H

#include <windows.h>

class AzulStopWatch
{
public:
	static void initStopWatch();

	AzulStopWatch()
	{
		this->reset();
	}

	void tic();
	void toc();
	void reset();
	float timeInSeconds();

private:	
	LARGE_INTEGER getStopWatch();

	static float SecondsPerCycle;
	LARGE_INTEGER ticTime;
	LARGE_INTEGER tocTime;
	LARGE_INTEGER deltaTime;
	float		  timeSeconds;

};

#endif AZUL_STOP_WATCH_H