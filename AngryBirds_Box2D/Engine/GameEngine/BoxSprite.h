#ifndef BOX_SPRITE_H
#define BOX_SPRITE_H

#include "EnumName.h"
#include "Rect.h"
#include "Sprite.h"
#include "BoxModel.h"
#include "GameSprite.h"


class BoxSprite : public Sprite
{
public:
	BoxSprite( const char * const _Name, BoxModel * const p );
	BoxSprite( SpriteBatchName::Name spriteBatchName, SpriteName::Name spriteName, float lineWidth, const Vect &color, Rect destRect);
	BoxSprite(  SpriteBatchName::Name spriteBatchName, SpriteName::Name _spriteName, float _lineWidth, const Vect &_color, GameSprite *gSprite);

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
	void privBoxSprite(  SpriteBatchName::Name spriteBatchName, SpriteName::Name _spriteName, float _lineWidth, const Vect &_color, Rect destRect);

	// Hidden
	BoxModel *boxModel;
	SpriteName::Name spriteName;

};



#endif