 #ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "GameSprite.h"
#include "BoxSprite.h"
#include "Box2D/Common/b2Math.h"
class b2Body;

class GameObject
{
public:
	GameObject(  );
	virtual ~GameObject();
	virtual void update( b2Vec2 posInMeters, float angleInRadians ) = 0;
	virtual void ApplyDamage(float damage) = 0;

	GameSprite  *pGameSprite;

	b2Body		*pBody;

	b2Vec2	pos;
	float	angle;
	GameObjectName::Name	gameObjName;
	int health;
	bool isAlive;
	bool markedfordeath;
	bool GameObject::IsMarked();
	void GameObject::MarkforDeath();
};





#endif