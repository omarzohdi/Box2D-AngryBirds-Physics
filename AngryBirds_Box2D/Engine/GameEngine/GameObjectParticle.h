#ifndef GAME_OBJECT_PART_H
#define GAME_OBJECT_PART_H

#include "GameSprite.h"
#include "GameObject.h"
#include "CircleSprite.h"
#include "Box2D/Common/b2Math.h"

class b2Body;

class GameObjectParticle: public GameObject
{
public:
	
	GameObjectParticle( GameObjectName::Name name, GameSprite *pGameSprite, CircleSprite *pDebugSprite );
	void update( b2Vec2 posInMeters, float angleInRadians ) override;
	void ApplyDamage(float damage) override;

	CircleSprite	*pCircleSprite;
};

#endif