#ifndef GAME_OBJECT_SLING_H
#define GAME_OBJECT_SLING_H

#include "GameSprite.h"
#include "BoxSprite.h"
#include "Box2D/Common/b2Math.h"
class b2Body;

class GameObjectSlingshot: public GameObject
{
public:
	
	GameObjectSlingshot( GameObjectName::Name name, GameSprite *pGameSprite, GameSprite *pGameSprite2, BoxSprite *pDebugSprite );
	void update( b2Vec2 posInMeters, float angleInRadians ) override;
	void ApplyDamage(float damage) override;

	BoxSprite	*pBoxSprite;
	GameSprite *pUpperSprite;

};

#endif