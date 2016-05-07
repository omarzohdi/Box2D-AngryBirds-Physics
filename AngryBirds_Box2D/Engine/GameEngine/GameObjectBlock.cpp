
#include "PixelToMeter.h"
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "GameObjectBlock.h"
#include "Image.h"
#include "World.h"
#include "ParticleEmitter.h"
#include "irrKlang.h"
using namespace irrklang;
extern ISoundEngine	*pSndEngine;
//class World;


void GameObjectBlock::PlayDamageSound()
{
	if (this->type == BlockType::Stone)
		pSndEngine->play2D("StoneDamage.mp3", false);
	else if (this->type == BlockType::Wood)
		pSndEngine->play2D("WoodDamage.mp3", false);
	else if (this->type == BlockType::Glass)
		pSndEngine->play2D("GlassDamage.mp3", false);
}

void  GameObjectBlock::PlayDestroySound()
{
		if (this->type == BlockType::Stone)
			pSndEngine->play2D("StoneDestroy.mp3", false);
		else if (this->type == BlockType::Wood)
			pSndEngine->play2D("WoodDestroy.mp3", false);
		else if (this->type == BlockType::Glass)
			pSndEngine->play2D("GlassDestroy.mp3", false);
}
ImageName::Name GameObjectBlock::getNextImageName( int health)
{
	ImageName::Name currentImage = this->pGameSprite->spriteModel->pImage->imageName;
	switch( this->damage )
	{
		case -1:
			if (health <= 15)
			{
				this->damage++;
				ImageName::Name newImage = (ImageName::Name)((int)currentImage + this->damage);
				this->PlayDamageSound();
				return newImage;
			}
			break;

		case 0:
			if (health <= 10)
			{
				this->damage++;
				ImageName::Name newImage = (ImageName::Name)((int)currentImage + this->damage);
				this->PlayDamageSound();
				return newImage;
			}
			break;

		case 1:
			if (health <= 5)
			{
				this->damage++;
				ImageName::Name newImage = (ImageName::Name)((int)currentImage + this->damage);
				this->PlayDamageSound();
				return newImage;
			}
			break;

		default:
			return currentImage;
	}

	return currentImage;
}


GameObjectBlock::GameObjectBlock( GameObjectName::Name name, GameSprite *gSprite,  BoxSprite *dSprite, BlockType type)
{
	this->gameObjName = name;
	this->pGameSprite = gSprite;
	this->pBoxSprite = dSprite;
	this->pBody = 0;

	
	this->pos.x = dSprite->posX;
	this->pos.y = dSprite->posY;
	this->angle = dSprite->angle;

	this->type = type;
	this->damage = -1;

}


void GameObjectBlock::update( b2Vec2 posInMeters, float angleInRadians ) 
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
		this->pBoxSprite->posX  = pos.x;
		this->pBoxSprite->posY = pos.y;
		this->pBoxSprite->angle = angle;

		pFix = pFix->GetNext();
	}

}

void GameObjectBlock::ApplyDamage(float damage)
{
	this->health -= (int)damage;

	if (health <= 0)
	{
		if (!markedfordeath)
		{
			PlayDestroySound();
			
			assert(this->type != 0);
		}

		this->MarkforDeath();
		health = 0;
		
	}

	ImageName::Name newName = this->getNextImageName(this->health);

	this->pGameSprite->spriteModel->SwapImage(newName);

}

