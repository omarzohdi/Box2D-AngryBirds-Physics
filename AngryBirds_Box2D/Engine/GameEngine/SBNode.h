#ifndef SBNODE_H
#define SBNODE_H

#include "Container.h"
#include "SpriteBatch.h"
#include "EnumName.h"

class SBNode : public Container
{
public:
	SBNode();

	void Set(SpriteBatchName::Name _batchName, SpriteBatch * batch);
	void addSprite(SpriteName::Name _spriteName, Sprite * _sprite);

	ContainerLink * privGetNewObj();

	EnumName getName();
	
public:
	SpriteBatch * batch;
	SpriteBatchName::Name batchName;

	void privDraw();
};

#endif