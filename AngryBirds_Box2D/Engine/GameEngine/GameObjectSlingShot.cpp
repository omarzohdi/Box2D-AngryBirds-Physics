#include "PixelToMeter.h"
#include "GameObject.h"
#include "Box2D.h"
#include "GameObjectSlingshot.h"


GameObjectSlingshot::GameObjectSlingshot( GameObjectName::Name name, GameSprite *gSprite, GameSprite *gSprite2,  BoxSprite *dSprite)
{
	this->gameObjName = name;
	this->pGameSprite = gSprite;
	this->pUpperSprite = gSprite2;
	this->pBoxSprite = dSprite;
	this->pBody = 0;

	
	this->pos.x = gSprite->posX;
	this->pos.y = gSprite->posY;
	this->angle = dSprite->angle;
}


void GameObjectSlingshot::update( b2Vec2 posInMeters, float angleInRadians ) 
{

	posInMeters;
	angleInRadians;
}

void GameObjectSlingshot::ApplyDamage(float damage)
{
	damage;
}