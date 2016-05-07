#ifndef GAME_OBJECT_SMOKE_H
#define GAME_OBJECT_SMOKE_H

#include "GameSprite.h"
#include "CircleSprite.h"
#include "Box2D/Common/b2Math.h"

class GameObjectSmokeCloud: public GameObject
{
public:
	
	GameObjectSmokeCloud( GameObjectName::Name name, GameSprite *pGameSprite, Rect*);
	void update( b2Vec2 posInMeters, float angleInRadians ) override;
	~GameObjectSmokeCloud();
};

#endif