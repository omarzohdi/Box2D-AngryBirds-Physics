#ifndef GAME_OBJECT_GROUND_H
#define GAME_OBJECT_GROUND_H

#include "GameSprite.h"
#include "BoxSprite.h"
#include "Box2D/Common/b2Math.h"
class b2Body;

class GameObjectGround: public GameObject
{
public:
	
	GameObjectGround( GameObjectName::Name name, GameSprite *pGameSprite, BoxSprite *pDebugSprite );
	void update( b2Vec2 posInMeters, float angleInRadians ) override;
	void ApplyDamage(float damage) override;
	
	ImageName::Name getNextImageName( int health, ImageName::Name currName );

	BoxSprite	*pBoxSprite;

};

#endif