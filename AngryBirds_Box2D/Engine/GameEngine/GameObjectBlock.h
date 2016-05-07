#ifndef GAME_OBJECT_BLOCK_H
#define GAME_OBJECT_BLOCK_H

#include "GameSprite.h"
#include "BoxSprite.h"
#include "Box2D/Common/b2Math.h"
class b2Body;

enum BlockType
{
	Wood= 1,
	Stone,
	Glass
};

class GameObjectBlock: public GameObject
{
public:
	
	GameObjectBlock( GameObjectName::Name name, GameSprite *pGameSprite, BoxSprite *pDebugSprite , BlockType type);
	void update( b2Vec2 posInMeters, float angleInRadians ) override;
	void ApplyDamage(float damage) override;
	
	ImageName::Name getNextImageName( int health);

	BoxSprite	*pBoxSprite;

	BlockType type;
	int damage;

private:
	void PlayDamageSound();
	void PlayDestroySound();

};

#endif