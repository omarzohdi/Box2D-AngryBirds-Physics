/*
 * Timer.cpp
 *
 * Common timer implementation across all platforms.
 */

//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------
#include "Timer.h"


//---------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTORS / ASSIGNMENT:
//---------------------------------------------------------------------------
Timer::Timer(): _ticMark( TIME_MAX )
{ }


Timer::~Timer()	
{ }


//---------------------------------------------------------------------------
// TIMING METHODS:
//---------------------------------------------------------------------------
void Timer::tic()
{
	this->_ticMark = Timer::getSystemTime();
}


const Time Timer::toc() const
{
	Time elapsedTime;

	// If tick has been called...
	if ( Time(TIME_MAX) != this->_ticMark )
	{
		elapsedTime = Timer::getSystemTime() - this->_ticMark;
	}

	return( elapsedTime );
}

