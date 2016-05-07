#ifndef SPRITE_NODE_H
#define SPRITE_NODE_H

#include "ContainerLink.h"
//class GameSprite;
class Sprite;

class SpriteNode : public ContainerLink
{
public:
	SpriteNode();

	void Set(SpriteName::Name _spriteName, Sprite * _sprite);

	EnumName getName();


public:

	Sprite *pSprite;
	SpriteName::Name spriteName;

};


#endif