#ifndef GAME_OBJECT_BIRD_H
#define GAME_OBJECT_BIRD_H

#include "GameSprite.h"
#include "CircleSprite.h"
#include "Box2D/Common/b2Math.h"

class b2Body;

enum BirdState
{
	NORMAL,
	MOVING,
	FLYING,
	JUMPING,
	WAITING
};
enum BirdType
{
	RED_BIRD,
	YELLOW_BIRD,
	BLACK_BIRD,
	WHITE_BIRD,
	BLUE_BIRD,
	GREEN_BIRD

};
class GameObjectBird: public GameObject
{
public:
	
	GameObjectBird( GameObjectName::Name name, GameSprite *pGameSprite, CircleSprite *pDebugSprite, BirdType intype);
	void update( b2Vec2 posInMeters, float angleInRadians) override;
	void ApplyDamage(float damage) override;
	
	void JumpAnim();
	void LEROYJENKINS();
	void blue_createClone(float,float,GameObjectBird*,b2Vec2);
	void BlinkOpen(bool isBlinking);
	void DamageSprite();

	CircleSprite	*pCircleSprite;
	
	BirdState state;
	bool active;
	b2Vec2   origpos;
	bool launched;

	BirdType type;
	bool powerused;

	b2Vec2 prevpos;

	int Blink;
	int Open;
};

#endif