/*
 *  Timer.cpp
*/

#include <windows.h>
#include <assert.h>

#include "AzulStopWatch.h"

float AzulStopWatch::SecondsPerCycle = 0.0f;

void AzulStopWatch::initStopWatch() 
{
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	SecondsPerCycle = 1.0f / Frequency.QuadPart;
}

LARGE_INTEGER AzulStopWatch::getStopWatch()
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return time;
}

void AzulStopWatch::tic()
{
	ticTime = this->getStopWatch();
}

void AzulStopWatch::toc()
{
	tocTime = this->getStopWatch();
	assert( tocTime.QuadPart >= ticTime.QuadPart );
	deltaTime.QuadPart = tocTime.QuadPart - ticTime.QuadPart;
}

void AzulStopWatch::reset()
{
	LARGE_INTEGER tmpTime = this->getStopWatch();
	ticTime.QuadPart = tmpTime.QuadPart;
	tocTime.QuadPart =  tmpTime.QuadPart;
	deltaTime.QuadPart = 0;
}

float AzulStopWatch::timeInSeconds()
{
	float floatTime;
	floatTime = static_cast<float>(deltaTime.QuadPart);
	floatTime *= SecondsPerCycle;
	return floatTime;
}