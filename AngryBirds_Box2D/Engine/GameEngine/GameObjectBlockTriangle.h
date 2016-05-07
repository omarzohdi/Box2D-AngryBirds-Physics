#ifndef GAME_OBJECT_BLOCKT_H
#define GAME_OBJECT_BLOCKT_H


#include "GameSprite.h"
#include "CircleSprite.h"
#include "GameObjectBlock.h"
#include "Box2D/Common/b2Math.h"

class b2Body;
class PolySprite;

class GameObjectBlockTriangle: public GameObject
{
public:
	
	GameObjectBlockTriangle( GameObjectName::Name name, GameSprite *pGameSprite, PolySprite *pDebugSprite , BlockType type);
	void update( b2Vec2 posInMeters, float angleInRadians ) override;
	void ApplyDamage(float damage) override;
	
	ImageName::Name getNextImageName( int health);

	PolySprite *pPolySprite;

	BlockType type;
	int damage;

private:
	void PlayDamageSound();
	void PlayDestroySound();

};

#endif