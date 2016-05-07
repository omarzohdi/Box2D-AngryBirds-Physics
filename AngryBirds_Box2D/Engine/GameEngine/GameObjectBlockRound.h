#ifndef GAME_OBJECT_BLOCKR_H
#define GAME_OBJECT_BLOCKR_H

#include "GameSprite.h"
#include "CircleSprite.h"
#include "GameObjectBlock.h"
#include "Box2D/Common/b2Math.h"
class b2Body;

class GameObjectBlockRound: public GameObject
{
public:
	
	GameObjectBlockRound( GameObjectName::Name name, GameSprite *pGameSprite, CircleSprite *pDebugSprite , BlockType type);
	void update( b2Vec2 posInMeters, float angleInRadians ) override;
	void ApplyDamage(float damage) override;
	
	ImageName::Name getNextImageName( int health);

	CircleSprite *pCircleSprite;

	BlockType type;
	int damage;

private:
	void PlayDamageSound();
	void PlayDestroySound();

};

#endif