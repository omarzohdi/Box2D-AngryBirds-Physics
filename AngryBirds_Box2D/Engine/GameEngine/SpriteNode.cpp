#include "SpriteNode.h"

SpriteNode::SpriteNode()
{
	this->spriteName = SpriteName::Not_Initialized;
	this->pSprite = 0;
}

void SpriteNode::Set(SpriteName::Name _spriteName, Sprite * _sprite)
{
	this->spriteName = _spriteName;
	this->pSprite = _sprite;
}

EnumName SpriteNode::getName()
{
	return SpriteName( (EnumName::Name)this->spriteName );
}