
#include "PixelToMeter.h"
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "GameObjectParticle.h"

//#include "World.h"


/*TODO CORRECT RESPAWN OF BIRD
	ADD MOR POWERSSSS! */
class World;

GameObjectParticle::GameObjectParticle( GameObjectName::Name name, GameSprite *gSprite,  CircleSprite *dSprite)
{
	this->gameObjName = name;
	this->pGameSprite = gSprite;
	this->pCircleSprite = dSprite;
	this->pBody = 0;

	
	this->pos.x = dSprite->posX;
	this->pos.y = dSprite->posY;
	this->angle = dSprite->angle;

	this->health = 70;

}

void GameObjectParticle::update( b2Vec2 posInMeters, float angleInRadians ) 
{
	// updates position and angle from physics update
	this->pos.x = MeterToPixel( posInMeters.x );
	this->pos.y = MeterToPixel( posInMeters.y );
	this->angle = angleInRadians;

	b2Fixture *pFix = this->pBody->GetFixtureList();

	while( pFix != 0 )
	{
		GameObject *pGObj = (GameObject *)pFix->GetUserData();

		// push the values to the GameSprite
		pGObj->pGameSprite->posX = pos.x;
		pGObj->pGameSprite->posY = pos.y;
		pGObj->pGameSprite->angle = angle;

		// push the values to the DebugSprite
		this->pCircleSprite->posX  = pos.x;
		this->pCircleSprite->posY = pos.y;
		this->pCircleSprite->angle = angle;

		pFix = pFix->GetNext();
	}

}

void GameObjectParticle::ApplyDamage(float damage)
{
	this->health -= (int)damage;

	if (health <= 0)
	{
		this->MarkforDeath();
		health = 0;
	}

}