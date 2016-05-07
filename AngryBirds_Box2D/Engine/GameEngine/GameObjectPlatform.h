#ifndef GAME_OBJECT_PLAT_H
#define GAME_OBJECT_PLAT_H

#include "GameSprite.h"
#include "BoxSprite.h"
#include "Box2D/Common/b2Math.h"
class b2Body;

class GameObjectPlatform: public GameObject
{
public:
	
	GameObjectPlatform( GameObjectName::Name name, GameSprite *pGameSprite, BoxSprite *pDebugSprite );
	void update( b2Vec2 posInMeters, float angleInRadians ) override;
	void ApplyDamage(float damage) override;

	BoxSprite	*pBoxSprite;

};

#endif