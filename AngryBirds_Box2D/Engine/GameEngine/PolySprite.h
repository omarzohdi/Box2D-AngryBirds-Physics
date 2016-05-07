#ifndef POLY_SPRITE_H
#define POLY_SPRITE_H

#include "EnumName.h"
#include "Rect.h"
#include "Sprite.h"
#include "Vect2D.h"
#include "PolyModel.h"

class PolySprite : public Sprite
{
public:

	enum LineType
	{
		Loop = GL_LINE_LOOP,
		Strip = GL_LINE_STRIP,
		List = GL_LINES
	};


public:
	PolySprite( const char * const _Name, PolyModel * const p );
	PolySprite( SpriteBatchName::Name spriteBatchName, SpriteName::Name spriteName, float lineWidth, const Vect &color, Vect2D originPt, int numVerts, Vect2D *vertList, LineType type);

	float	angle;
	float	posX;
	float	posY;
	float	scaleX;
	float	scaleY;
	Vect	color;
	float	lineWidth;
	LineType type;

private:
	// must define, base class has abstract methods
	void transform( void );
	void draw( void );
	void setRenderState(void);

	void privDraw();

	// Hidden

	PolyModel *polyModel;
	SpriteName::Name spriteName;

};



#endif