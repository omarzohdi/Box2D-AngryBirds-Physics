#ifndef SCREEN_LINE_H
#define SCREEN_LINE_H

#include "EnumName.h"
#include "Rect.h"
#include "Sprite.h"
#include "Vect2D.h"
#include "ScreenLineModel.h"

class ScreenLine : public Sprite
{
public:
	ScreenLine( const char * const _Name, ScreenLineModel * const p );
	ScreenLine( SpriteBatchName::Name spriteBatchName, SpriteName::Name spriteName, float lineWidth, const Vect &color, Vect2D &ptA,  Vect2D &ptB);


	Vect2D	posA;
	Vect2D	posB;

	Vect	color;
	float	lineWidth;


private:
	// must define, base class has abstract methods
	void transform( void );
	void draw( void );
	void setRenderState(void);

	void privDraw();

	// Hidden

	ScreenLineModel *screenLineModel;
	SpriteName::Name spriteName;

};



#endif