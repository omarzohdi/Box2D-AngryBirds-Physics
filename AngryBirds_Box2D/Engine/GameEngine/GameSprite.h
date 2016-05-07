#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include "Sprite.h"
#include "EnumName.h"
#include "Rect.h"
#include "SpriteModel.h"


class GameSprite : public Sprite
{
public:
	GameSprite( const char * const _Name, SpriteModel * const p );
	GameSprite( SpriteBatchName::Name spriteBatchName, SpriteName::Name spriteName, ImageName::Name imageName, Rect destRect);

	float	angle;
	float	posX;
	float	posY;
	float	scaleX;
	float	scaleY;

	float   origWidth;
	float	origHeight;

	SpriteModel *spriteModel;

private:
	// must define, base class has abstract methods
	void transform( void );
	void draw( void );
	void setRenderState(void);

	// User control
	void privDraw();

	// Hidden
	
	SpriteName::Name spriteName;

};



#endif