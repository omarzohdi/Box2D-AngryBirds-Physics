#ifndef GAME_OBJECT_PIG_H
#define GAME_OBJECT_PIG_H

#include "GameSprite.h"
#include "CircleSprite.h"
#include "Box2D/Common/b2Math.h"
class b2Body;

class GameObjectPig: public GameObject
{
public:
	
	GameObjectPig( GameObjectName::Name name, GameSprite *pGameSprite, CircleSprite *pDebugSprite , bool Helmet = false);
	void update( b2Vec2 posInMeters, float angleInRadians ) override;
	void ApplyDamage(float damage) override;
	void BlinkOpen(bool OPBL);

	CircleSprite	*pCircleSprite;

	int Open;
	int Blink;

	bool Helmet;
	bool Hurt;
};

#endif