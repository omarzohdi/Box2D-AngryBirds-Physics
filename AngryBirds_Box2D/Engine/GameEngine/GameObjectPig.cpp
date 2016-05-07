
#include "PixelToMeter.h"
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "GameObjectPig.h"

#include "irrKlang.h"
using namespace irrklang;
extern ISoundEngine	*pSndEngine;

GameObjectPig::GameObjectPig( GameObjectName::Name name, GameSprite *gSprite,  CircleSprite *dSprite, bool Helmet)
{
	this->gameObjName = name;
	this->pGameSprite = gSprite;
	this->pCircleSprite = dSprite;
	this->pBody = 0;

	
	this->pos.x = dSprite->posX;
	this->pos.y = dSprite->posY;
	this->angle = dSprite->angle;

	Blink = 0;
	Open = 0;
	Hurt = false;
	this->Helmet = Helmet;

	if (Helmet)
		health *= 2;
}


void GameObjectPig::update( b2Vec2 posInMeters, float angleInRadians ) 
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


	if (health >=0)
	{
		if (Blink == 122.0f)
		{
			
			if (Open == 0)
			{
				BlinkOpen(true);
				Open++;
			}
			else
			{
				if (Open == 10)
				{	
					BlinkOpen(false);

					Blink = 0;
					Open = 0;
				}
				else
				{
					Open++;
				}
			}
		}
		else
		{
			Blink++;
		}
	}
}




void GameObjectPig::ApplyDamage(float damage)
{
	this->health -= (int)damage;
	if (health <= 15)
	{
		if (!Hurt)
		{
			if (this->Helmet)
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_HelmetPigHurt1);
			else
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_PigHurt);

			Hurt = true;
		}
	}

	if (health <= 0)
	{
		this->MarkforDeath();
		health = 0;
		pSndEngine->play2D("PigDestroy.mp3", false);
	}

}

void GameObjectPig::BlinkOpen(bool isBlinking)
{
	if (isBlinking)
	{

		if (this->Helmet)
		{
			if (!this->Hurt)
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_HelmetPigBlink);
			else
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_HelmetPigHurt1Blink);
		}
		else
		{
			if (!this->Hurt)
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_PigBlink);
			else
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_PigHurt);
		}

	}
	else
	{
		if (this->Helmet)
		{
			if (!this->Hurt)
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_HelmetPig);
			else
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_HelmetPigHurt1);
		}
		else
		{
			if (!this->Hurt)
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_Pig);
			else
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_PigHurt);
		}
	}
}