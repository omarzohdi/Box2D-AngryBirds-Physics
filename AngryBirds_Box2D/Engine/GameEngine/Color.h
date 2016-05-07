#include "MathEngine.h"

#ifndef COLOR_H
#define COLOR_H


	enum color
	{
		Red,
		Blue,
		Green,
		White,
		Black,
		Yellow,
	};

class Color
{
public:
	Color(  color t)
	{	
		this->colorType = t;

		switch( t )
		{
		case Red:
			this->data.set(0xff, 0x00, 0x00, 0xff);
			break;

		case Blue:
			this->data.set(0x00, 0x00, 0xFF, 0xff);
			break;

		case Green:
			this->data.set(0x00, 0xFF, 0x00, 0xff);
			break;

		case White:
			this->data.set(0xff, 0xFF, 0xFF, 0xff);
			break;

		case Black:
			this->data.set(0x00, 0x00, 0x00, 0xff);
			break;

		case Yellow:
			this->data.set(0xFF, 0xFF, 0x00, 0xff);
			break;

		default:
			assert(0);
		}

	}

	operator Vect ()
	{
		return this->data;
	}

	color colorType;
	Vect  data;

};

#endif