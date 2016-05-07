#include "PixelToMeter.h"
#include "GameObject.h"
#include "Box2D.h"
#include "GameObjectPlatform.h"


GameObjectPlatform::GameObjectPlatform( GameObjectName::Name name, GameSprite *gSprite,  BoxSprite *dSprite)
{
	this->gameObjName = name;
	this->pGameSprite = gSprite;
	this->pBoxSprite = dSprite;
	this->pBody = 0;

	
	this->pos.x = dSprite->posX;
	this->pos.y = dSprite->posY;
	this->angle = dSprite->angle;

}


void GameObjectPlatform::update( b2Vec2 posInMeters, float angleInRadians ) 
{
		// updates position and angle from physics update
	this->pos.x = MeterToPixel( posInMeters.x );
	this->pos.y = MeterToPixel( posInMeters.y );
	this->angle = angleInRadians;

	b2Fixture *pFix = this->pBody->GetFixtureList();

	while( pFix != 0 )
	{
		GameObject *pGObj = (GameObject *)pFix->GetUserData();
		
		if (pGObj == 0 ) assert(false);

		// push the values to the GameSprite
		pGObj->pGameSprite->posX = pos.x;
		pGObj->pGameSprite->posY = pos.y;
		pGObj->pGameSprite->angle = angle;

		// push the values to the DebugSprite
		this->pBoxSprite->posX  = pos.x;
		this->pBoxSprite->posY = pos.y;
		this->pBoxSprite->angle = angle;

		pFix = pFix->GetNext();
	}

}
void GameObjectPlatform::ApplyDamage(float damage)
{
	damage;
}