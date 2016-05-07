#include "SBNode.h"
#include "SpriteNode.h"
#include "Sprite.h"

SBNode::SBNode()
{
	this->batchName = SpriteBatchName::Not_Initialized;
	this->batch = 0;
}

void SBNode::Set(SpriteBatchName::Name _batchName, SpriteBatch * _batch)
{
	batchName = _batchName;
	batch = _batch;
}

void SBNode::privDraw()
{
	ContainerLink * ptr = this->active;

	while(ptr != 0)
	{
		((SpriteNode *)ptr)->pSprite->Draw();

		ptr = ptr->next;
	}

}

void SBNode::addSprite(SpriteName::Name _spriteName, Sprite * _sprite)
{
	SpriteNode * node = new SpriteNode();

	node->Set(_spriteName, _sprite);

	this->privActiveAddToFront((ContainerLink *)node, this->active);
}

ContainerLink * SBNode::privGetNewObj()
{
	ContainerLink * pObj = new SpriteNode();
	return pObj;
}

EnumName SBNode::getName()
{
	return SpriteBatchName( (EnumName::Name)this->batchName );
}