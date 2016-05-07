#ifndef GAME_OBJECT_EGG_H
#define GAME_OBJECT_EGG_H

#include "GameSprite.h"
#include "CircleSprite.h"
#include "Box2D/Common/b2Math.h"

class b2Body;

class GameObjectEgg: public GameObject
{
public:
	
	GameObjectEgg( GameObjectName::Name name, GameSprite *pGameSprite, CircleSprite *pDebugSprite );
	void update( b2Vec2 posInMeters, float angleInRadians ) override;
	void ApplyDamage(float damage) override;

	CircleSprite	*pCircleSprite;
};

#endif