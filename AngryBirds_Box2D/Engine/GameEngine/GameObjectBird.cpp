
#include "PixelToMeter.h"
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"
#include "GameObjectBird.h"
#include "irrKlang.h"
#include "World.h"


extern bool startworld;
extern int randomVal;

#include "irrKlang.h"
using namespace irrklang;
extern ISoundEngine	*pSndEngine;

/*TODO CORRECT RESPAWN OF BIRD
	ADD MOR POWERSSSS! */
class World;

extern b2Vec2 EXPLOSIONPOINT;
extern b2Vec2 POWERPOINT;


GameObjectBird::GameObjectBird( GameObjectName::Name name, GameSprite *gSprite,  CircleSprite *dSprite, BirdType intype)
{
	this->gameObjName = name;
	this->pGameSprite = gSprite;
	this->pCircleSprite = dSprite;
	this->pBody = 0;

	
	this->pos.x = dSprite->posX;
	this->pos.y = dSprite->posY;
	this->angle = dSprite->angle;

	this->origpos.x = dSprite->posX;
	this->origpos.y = dSprite->posY;	
	
	this->prevpos.x = dSprite->posX;
	this->prevpos.y = dSprite->posY;	

	this-> state = WAITING;
	this-> active = false;
	this-> launched = false;

	this->type = intype;
	this->powerused = false;

	this->health = 50;

	this->Blink = 0;
	this->Open = 0;
}

void GameObjectBird::JumpAnim()
{
	if (startworld && randomVal % 10 == 0)
	{
		if (state == WAITING)
		{
			this->pBody->SetActive(true);
			this->pBody->ApplyLinearImpulse( b2Vec2(0.0f, 5.0f) , this->pBody->GetPosition() , true);
			
			this->state = JUMPING;
		}
		else if (state == JUMPING)
		{
			this->pBody->SetAngularVelocity(0.0f);
			if (this->pBody->GetLinearVelocity().Length() <= 0)
			{
				state = WAITING;
				this->pBody->SetActive(false);
			}
		}
	}

}
void GameObjectBird::LEROYJENKINS()
{
	if (!powerused)
	{
		switch(this->type)
		{
			case BLUE_BIRD:
			
				World::getInstance().CreateNewGameObject( this->pos.x , this->pos.y + 35,this,b2Vec2(0.0f,10.0f), GameObjectName::GameObject_Bird );
				World::getInstance().CreateNewGameObject( this->pos.x , this->pos.y - 35,this,b2Vec2(0.0f,-10.0f), GameObjectName::GameObject_Bird);
				POWERPOINT = this->pBody->GetPosition();

			break;

			case YELLOW_BIRD:

				this->pBody->ApplyLinearImpulse(b2Vec2(this->pBody->GetLinearVelocity().x * 2.0f,this->pBody->GetLinearVelocity().y * 2.0f), this->pBody->GetPosition(),true);
				pSndEngine->play2D("BirdBoost.mp3", false);
			break;

			case BLACK_BIRD:
				EXPLOSIONPOINT = this->pBody->GetPosition();

				this->ApplyDamage(100.0f);
				break;

			case WHITE_BIRD:

				this->pBody->ApplyLinearImpulse(b2Vec2(0.0f, 25.0f ), this->pBody->GetPosition(),true);
				World::getInstance().CreateNewGameObject( this->pos.x , this->pos.y - 30,this,b2Vec2(0.0f,-10.0f), GameObjectName::GameObject_Egg);
				POWERPOINT = this->pBody->GetPosition();

				break;
			case GREEN_BIRD:

				this->pBody->ApplyAngularImpulse( 2.0f , true);
				this->pBody->SetLinearVelocity(b2Vec2 (0.0f, this->pBody->GetLinearVelocity().y));
				this->pBody->ApplyLinearImpulse( b2Vec2( -50.0f, 0.0f), this->pBody->GetPosition() ,  true);
				pSndEngine->play2D("BirdBoomerang.mp3", false);
				break;
					

		}

		powerused = true;
	}
}
void GameObjectBird::update( b2Vec2 posInMeters, float angleInRadians) 
{
	if (this->launched)
	{
		if (this->pBody->GetLinearVelocity().Length() <= 0.05)
			this->ApplyDamage(100.0f);

		if (this->type == BirdType::BLACK_BIRD && this->health < 50)
		{
			this->health -= 5;

			if (this->health <= 5)
			{
				LEROYJENKINS();
			}
	
		}
	}

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

	float dist = this->pos.Length() -  this->prevpos.Length();

	if ( dist > 50 && this->health >= 50 && this->launched)
	{
		this->prevpos.x = this->pos.x;
		this->prevpos.y = this->pos.y;

		World::getInstance().CreateSmokeCloud(this->pos.x, this->pos.y);

	}

	
	if (Blink == 150.0f)
	{
			
		if (Open == 0)
		{
			if (!this->launched)
				BlinkOpen(true);
			Open++;
		}
		else
		{
			if (Open == 10)
			{	
				if (health >= 50)
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
	this->JumpAnim();

}

void GameObjectBird::ApplyDamage(float damage)
{
	if (this->health >= 50)
	{
		DamageSprite();
	}

	this->health -= (int)damage;

	if (health <= 0)
	{
		if (this->type != BirdType::BLACK_BIRD)
		{
			if (!markedfordeath)
			{
				pSndEngine->play2D("BirdDestroy.mp3", false);
			}
		}
		else
		{
			if (!markedfordeath)
				pSndEngine->play2D("BirdExplosion.mp3", false);
		}
		
		this->MarkforDeath();
		health = 0;
		
	}

}
void GameObjectBird::DamageSprite()
{
	switch(this->type)
	{
		case RED_BIRD:
			this->pGameSprite->spriteModel->SwapImage(ImageName::Image_RedBirdCaw);
		break;

		case BLUE_BIRD:
			this->pGameSprite->spriteModel->SwapImage(ImageName::Image_BlueBirdHurt );
		break;

		case YELLOW_BIRD:
			this->pGameSprite->spriteModel->SwapImage(ImageName::Image_YellowBirdAngry );
		break;

		case BLACK_BIRD:
			this->pGameSprite->spriteModel->SwapImage(ImageName::Image_BlackBirdBlink );
		break;

		case WHITE_BIRD:
			this->pGameSprite->spriteModel->SwapImage(ImageName::Image_WhiteBirdPoop );
		break;
		case GREEN_BIRD:
			this->pGameSprite->spriteModel->SwapImage(ImageName::Image_GreenBirdSmashed );
		break;
	}


}
void GameObjectBird::BlinkOpen(bool isBlinking)
{
	if (isBlinking)
	{
		switch(this->type)
		{
			case RED_BIRD:
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_RedBirdBlink );
			break;

			case BLUE_BIRD:
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_BlueBirdBlink );
			break;

			case YELLOW_BIRD:
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_YellowBirdBlink );
			break;

			case BLACK_BIRD:
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_BlackBirdBlink );
			break;

			case WHITE_BIRD:
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_WhiteBirdBlink );
			break;
			case GREEN_BIRD:
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_GreenBirdBlink );
			break;
		}


	}
	else
	{
		switch(this->type)
		{
			case RED_BIRD:
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_RedBird);
			break;

			case BLUE_BIRD:
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_BlueBird);
			break;

			case YELLOW_BIRD:
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_YellowBird);
			break;

			case BLACK_BIRD:
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_BlackBird);
			break;

			case WHITE_BIRD:
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_WhiteBird);
			break;
			case GREEN_BIRD:
				this->pGameSprite->spriteModel->SwapImage(ImageName::Image_GreenBird);
			break;
		}
	}
}