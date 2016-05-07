
#include "PixelToMeter.h"
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "GameObjectEgg.h"

#include "irrKlang.h"
using namespace irrklang;
extern ISoundEngine	*pSndEngine;
extern b2Vec2 EXPLOSIONPOINT;
class World;

GameObjectEgg::GameObjectEgg( GameObjectName::Name name, GameSprite *gSprite,  CircleSprite *dSprite)
{
	this->gameObjName = name;
	this->pGameSprite = gSprite;
	this->pCircleSprite = dSprite;
	this->pBody = 0;

	
	this->pos.x = dSprite->posX;
	this->pos.y = dSprite->posY;
	this->angle = dSprite->angle;

	this->health = 1;

}

void GameObjectEgg::update( b2Vec2 posInMeters, float angleInRadians ) 
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

void GameObjectEgg::ApplyDamage(float damage)
{
	this->health -= (int)damage;

	if (health <= 0)
	{
		if (!markedfordeath)
		{
			pSndEngine->play2D("BirdExplosion.mp3", false);
			EXPLOSIONPOINT = this->pBody->GetPosition();		
		}

		this->MarkforDeath();
		health = 0;

		
	}

}