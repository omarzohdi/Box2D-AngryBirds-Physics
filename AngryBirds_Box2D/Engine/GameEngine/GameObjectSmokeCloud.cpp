
#include "PixelToMeter.h"
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "GameObjectSmokeCloud.h"

#include "World.h"


/*TODO CORRECT RESPAWN OF BIRD
	ADD MOR POWERSSSS! */
class World;

GameObjectSmokeCloud::GameObjectSmokeCloud( GameObjectName::Name name, GameSprite *gSprite, Rect * rectangle)
{
	this->gameObjName = name;
	this->pGameSprite = gSprite;
	
	this->pos.x = rectangle->x;
	this->pos.y = rectangle->y;
	this->angle = 0.0f;

	this->health = 100;

}

GameObjectSmokeCloud::~GameObjectSmokeCloud()
{

}


void GameObjectSmokeCloud::update( b2Vec2 posInMeters, float angleInRadians ) 
{
	// updates position and angle from physics update
	this->pos.x = MeterToPixel( posInMeters.x );
	this->pos.y = MeterToPixel( posInMeters.y );
	this->angle = angleInRadians;
}
