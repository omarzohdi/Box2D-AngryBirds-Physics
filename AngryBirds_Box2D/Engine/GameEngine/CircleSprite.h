#ifndef CIRCLE_SPRITE_H
#define CIRCLE_SPRITE_H

#include "EnumName.h"
#include "Rect.h"
#include "Sprite.h"
#include "CircleModel.h"


class CircleSprite : public Sprite
{
public:
	CircleSprite( const char * const _Name, CircleModel * const p );
	CircleSprite( SpriteBatchName::Name spriteBatchName, SpriteName::Name spriteName, float lineWidth, const Vect &color, Rect destRect);
	

	float	angle;
	float	posX;
	float	posY;
	float	scaleX;
	float	scaleY;
	Vect	color;
	float	lineWidth;

	float   origWidth;
	float	origHeight;

private:
	// must define, base class has abstract methods
	void transform( void );
	void draw( void );
	void setRenderState(void);

	void privDraw();

	// Hidden


	CircleModel *circleModel;
	SpriteName::Name spriteName;

};



#endif