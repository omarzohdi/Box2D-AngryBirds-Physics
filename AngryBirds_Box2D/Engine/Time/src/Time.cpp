// Time.cpp

//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------
#include "Time.h"
#include <limits>   // For numeric_limits< Time::Representation >.


//---------------------------------------------------------------------------
// FRIENDS:
//---------------------------------------------------------------------------
const Time operator*( const float ratio, const Time& rhs )
{
	return(
		Time( static_cast< Time::Representation >( ratio * rhs._rawTime ) )
  	);
}

const Time operator*( const int ratio, const Time& rhs )
{
	return( Time( ratio * rhs._rawTime ) );
}



//---------------------------------------------------------------------------
// CONSTRUCTORS:
//---------------------------------------------------------------------------

Time::Time( const Duration duration ): _rawTime( 0 )
{
	// IMPORTANT: This is private information that is SUBJECT TO CHANGE!
	//
	// Currently: 1 second = 30000
	//            1 ms     = 30
	//            1 NTSC   = 500
	//            1 PAL    = 600
	//
	// At 32 bits, this gives us a range of roughly -20 to 20 hours.
	const Time::Representation ONE_RAW_SECOND = 30000;

	switch ( duration )
	{
		case TIME_ZERO:
			this->_rawTime = 0;
			break;

		case TIME_NTSC_FRAME:
			this->_rawTime = ONE_RAW_SECOND / 60;
			break;

		case TIME_NTSC_30_FRAME:
			this->_rawTime = 2 * ONE_RAW_SECOND / 60;
			break;

		case TIME_PAL_FRAME:
			this->_rawTime = ONE_RAW_SECOND / 50;
			break;

		case TIME_ONE_SECOND:
			this->_rawTime = ONE_RAW_SECOND;
			break;

		case TIME_ONE_MILLISECOND:
			this->_rawTime = ONE_RAW_SECOND / 1000;
			break;

		case TIME_ONE_MINUTE:
			this->_rawTime = 60 * ONE_RAW_SECOND;
			break;

		case TIME_ONE_HOUR:
			this->_rawTime = 60 * 60 * ONE_RAW_SECOND;
			break;

		case TIME_MIN:
			this->_rawTime = std::numeric_limits< Time::Representation >::min();
			break;

		case TIME_MAX:
			this->_rawTime = std::numeric_limits< Time::Representation >::max();
			break;

		default:
			// IMPORTANT: Intentionally avoiding assertion handling
			//            for the Time library.
			this->_rawTime = 0;
			break;
	}
}



//---------------------------------------------------------------------------
// COMPARISONS:
//---------------------------------------------------------------------------
bool Time::operator==( const Time& rhs ) const
{
	return( this->_rawTime == rhs._rawTime );
}


bool Time::operator!=( const Time& rhs ) const
{
	return( this->_rawTime != rhs._rawTime );
}


bool Time::operator<( const Time& rhs ) const
{
	return( this->_rawTime < rhs._rawTime );
}


bool Time::operator<=( const Time& rhs ) const
{
	return( this->_rawTime <= rhs._rawTime );
}


bool Time::operator>( const Time& rhs ) const
{
	return( this->_rawTime > rhs._rawTime );
}


bool Time::operator>=( const Time& rhs ) const
{
	return( this->_rawTime >= rhs._rawTime );
}



//---------------------------------------------------------------------------
// NEGATION / ADDITION / SUBTRACTION:
//---------------------------------------------------------------------------
const Time Time::operator-() const
{
	return( Time( -this->_rawTime ) );
}


const Time Time::operator+( const Time& rhs ) const
{
	// !!! FIXME: Overflow checks
	return( Time( this->_rawTime + rhs._rawTime ) );
}


const Time Time::operator-( const Time& rhs ) const
{
	// !!! FIXME: Overflow checks
	return( Time( this->_rawTime - rhs._rawTime ) );
}


Time& Time::operator+=( const Time& rhs )
{
	// !!! FIXME: Overflow checks
	this->_rawTime += rhs._rawTime;
	return( *this );
}


Time& Time::operator-=( const Time& rhs )
{
	// !!! FIXME: Overflow checks
	this->_rawTime -= rhs._rawTime;
	return( *this );
}



//---------------------------------------------------------------------------
// MULTIPLICATION:
//---------------------------------------------------------------------------
const Time Time::operator*( const float ratio ) const
{
	// !!! FIXME: Overflow checks
	return(
		Time( static_cast< Representation >( ratio * this->_rawTime ) )
		);
}


const Time Time::operator*( const int ratio ) const
{
	// !!! FIXME: Overflow checks
	return( Time( this->_rawTime * ratio ) );
}


Time& Time::operator*=( const float ratio )
{
	// !!! FIXME: Overflow checks
	this->_rawTime = static_cast< Representation>( ratio * this->_rawTime );
	return( *this );
}


Time& Time::operator*=( const int ratio )
{
	// !!! FIXME: Overflow checks
	this->_rawTime *= ratio;
	return( *this );
}



//---------------------------------------------------------------------------
// DIVISION:
//---------------------------------------------------------------------------
float Time::operator/( const Time& denominator ) const
{
	// !!! FIXME: Divide by zero.
	return(
		static_cast< float >( this->_rawTime ) / denominator._rawTime
		);
}


const Time Time::operator/( const float denominator ) const
{
	// !!! FIXME: Divide by zero.
	return(
		Time( static_cast< Representation >( this->_rawTime / denominator ) )
		);
}


const Time Time::operator/( const int denominator ) const
{
	// !!! FIXME: Divide by zero.
	return( Time( this->_rawTime / denominator ) );
}


Time& Time::operator/=( const float denominator )
{
	// !!! FIXME: Divide by zero.
	this->_rawTime = 
		static_cast< Representation>( this->_rawTime / denominator );
	return( *this );
}


Time& Time::operator/=( const int denominator )
{
	// !!! FIXME: Divide by zero.
	this->_rawTime /= denominator;
	return( *this );
}



//---------------------------------------------------------------------------
// DIVISION:
//---------------------------------------------------------------------------
int 	Time::quotient( const Time& numerator, const Time& denominator )
{
	// !!! FIXME: Divide by zero & check range
	return(static_cast< int > (numerator._rawTime / denominator._rawTime ));
}


const Time 	Time::remainder( const Time& numerator, const Time& denominator )
{
	// !!! FIXME: Divide by zero.
	return( Time( numerator._rawTime % denominator._rawTime ) );
}


//---------------------------------------------------------------------------
// PRIVATE IMPLEMENTATION:
//---------------------------------------------------------------------------
Time::Time( const Time::Representation rawTime ): _rawTime( rawTime )
{
}

