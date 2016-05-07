#include "AngryContactListener.h"

#include "Image.h"
#include "World.h"

#include "ParticleEmitter.h"
#include "irrKlang.h"
using namespace irrklang;
extern ISoundEngine	*pSndEngine;
extern ISound	*pSndTheme;


AngryContactListener::AngryContactListener()
{
}

void AngryContactListener::BeginContact(b2Contact* pContact)
{ /* handle begin event */ 
	b2WorldManifold worldManiforld;
	pContact->GetWorldManifold( &worldManiforld );

	
	GameObject *gObjA = (GameObject *)pContact->GetFixtureA()->GetBody()->GetUserData();
	GameObject *gObjB = (GameObject *)pContact->GetFixtureB()->GetBody()->GetUserData();

	if (gObjA == 0 || gObjB ==0)
		return;

	b2Vec2 VelocityA = gObjA->pBody->GetLinearVelocityFromWorldPoint(worldManiforld.points[0]);
	b2Vec2 VelocityB = gObjB->pBody->GetLinearVelocityFromWorldPoint(worldManiforld.points[0]);
	b2Vec2 Impact = VelocityA - VelocityB;

	float totaldamage = Impact.Length();

	if (gObjA->gameObjName == GameObjectName::GameObject_Bird || gObjA->gameObjName == GameObjectName::GameObject_Pig) 
		gObjA->pBody->SetAngularDamping(3.0f);
	if (gObjB->gameObjName == GameObjectName::GameObject_Bird || gObjB->gameObjName == GameObjectName::GameObject_Pig)
		gObjB->pBody->SetAngularDamping(3.0f);

	if (totaldamage > MATH_TOLERANCE)
	{
		float modA = 1.5f;
		float modB = 1.5f;

		if (gObjA->gameObjName ==  GameObjectName::GameObject_Block)
			modA = getTypeModifier( ((GameObjectBlock *)(gObjA))->type);
		if (gObjB->gameObjName ==  GameObjectName::GameObject_Block)
			modB = getTypeModifier( ((GameObjectBlock *)(gObjB))->type);

		if (gObjA->gameObjName == GameObjectName::GameObject_Bird && ((GameObjectBird *)gObjA)->launched)
		{
			gObjA->ApplyDamage(totaldamage /modA);

			if (totaldamage > 5.0f)
			{
				b2Vec2 SpawnPosition( gObjA->pBody->GetPosition().x, gObjA->pBody->GetPosition().y);
				float Width = PixelToMeter( gObjA->pGameSprite->origWidth / 2 );
				float height = PixelToMeter( gObjB->pGameSprite->origHeight /2);

				World::getInstance().FeatherEmitter->MarkPoistionforAdd(b2Vec2( SpawnPosition.x - Width, SpawnPosition.y + height), b2Vec2( -0.01f, 0.01f ) );
				World::getInstance().FeatherEmitter->MarkPoistionforAdd(b2Vec2( SpawnPosition.x, SpawnPosition.y), b2Vec2( 0.0f , 0.01f ) );
				World::getInstance().FeatherEmitter->MarkPoistionforAdd(b2Vec2( SpawnPosition.x + Width, SpawnPosition.y + height), b2Vec2( 0.01f, 0.01f) );
			}
		}
		else if (gObjA->gameObjName != GameObjectName::GameObject_Bird)
		{
			gObjA->ApplyDamage(totaldamage /modA);
		}

		if (gObjB->gameObjName == GameObjectName::GameObject_Bird && ((GameObjectBird *)gObjB)->launched)
		{
			if (totaldamage > 5.0f)
			{
				gObjB->ApplyDamage(totaldamage /modB);
				b2Vec2 SpawnPosition( gObjB->pBody->GetPosition().x, gObjB->pBody->GetPosition().y);
				float Width = PixelToMeter( gObjB->pGameSprite->origWidth / 2);
				float height = PixelToMeter( gObjB->pGameSprite->origHeight /2);

				World::getInstance().FeatherEmitter->MarkPoistionforAdd(b2Vec2( SpawnPosition.x - Width, SpawnPosition.y + height), b2Vec2( -0.01f, 0.01f ) );
				World::getInstance().FeatherEmitter->MarkPoistionforAdd(b2Vec2( SpawnPosition.x, SpawnPosition.y), b2Vec2( 0.0f , 0.01f ) );
				World::getInstance().FeatherEmitter->MarkPoistionforAdd(b2Vec2( SpawnPosition.x + Width, SpawnPosition.y + height), b2Vec2( 0.01f, 0.01f) );
			}
		}
		else if (gObjB->gameObjName != GameObjectName::GameObject_Bird)
		{
			gObjB->ApplyDamage(totaldamage /modB);
		}
	}
}


void AngryContactListener::EndContact(b2Contact* pContact)
{ /* handle end event */ 

	pContact;
}

void AngryContactListener::PreSolve(b2Contact* pContact, const b2Manifold* pManifold)
{ /* handle pre-solve event */
	pContact;pManifold;
	
	GameObject *gObjA = (GameObject *)pContact->GetFixtureA()->GetBody()->GetUserData();
	GameObject *gObjB = (GameObject *)pContact->GetFixtureB()->GetBody()->GetUserData();

	if (gObjA == 0 || gObjB ==0)
		return;

	if (gObjA->IsMarked() || gObjB->IsMarked() )
	{
		pContact->SetEnabled(false);
	}
}

void AngryContactListener::PostSolve(b2Contact* pContact, const b2ContactImpulse* pImpulse )
{ 
	pContact;
	pImpulse;
}

void AngryContactListener::CollideDynamics(GameObject * gObjA, GameObject * gObjB, const b2ContactImpulse * pImpulse)
{
		if (gObjA->health <= 20 && gObjA->health > 0)
		{
			float strength = (float)pImpulse->tangentImpulses[0];
			if (strength <= 0) strength *= -1;

			float mod = 1.5f;

			if (gObjA->gameObjName ==  GameObjectName::GameObject_Block)
				mod = getTypeModifier( ((GameObjectBlock *)(gObjA))->type);
			if (gObjB->gameObjName ==  GameObjectName::GameObject_Block)
				mod = getTypeModifier( ((GameObjectBlock *)(gObjB))->type);

			gObjA->health -= (int) (strength / mod);
			gObjB->health -= (int) (strength / mod);
			
			GameObjectBlock *pBlock = (GameObjectBlock * )gObjA;

			ImageName::Name oldName;
			oldName = pBlock->pGameSprite->spriteModel->pImage->imageName;  

			ImageName::Name newName;
			newName = pBlock->getNextImageName(gObjA->health);

			gObjA->pGameSprite->spriteModel->SwapImage(newName);
		}
}
void AngryContactListener::CollideStatic(GameObject * gObjA, const b2ContactImpulse * pImpulse)
{
		if (gObjA->health <= 20 && gObjA->health > 0)
		{

			/////Decrement Health////
			float strength = (float)pImpulse->tangentImpulses[0];
			if (strength <= 0) strength *= -1;

			float mod = 1.5f;

			if (gObjA->gameObjName ==  GameObjectName::GameObject_Block)
				mod = getTypeModifier( ((GameObjectBlock *)(gObjA))->type);

			gObjA->health -= (int) (strength / mod);

			////////Add Angular Dampening /////
			gObjA->pBody->SetAngularDamping(2.0f);
			
			////////Animate Image/////
			GameObjectBlock *pBlock = (GameObjectBlock * )gObjA;

			ImageName::Name oldName;
			oldName = pBlock->pGameSprite->spriteModel->pImage->imageName;  

			ImageName::Name newName;
			newName = pBlock->getNextImageName(gObjA->health);

			gObjA->pGameSprite->spriteModel->SwapImage(newName);
		}
}

int AngryContactListener::checkforstatic(GameObject * gObjA, GameObject * gObjB)
{
	if( (gObjA->gameObjName == GameObjectName::GameObject_WoodPlat || gObjA->gameObjName == GameObjectName::GameObject_Ground) &&
		(gObjB->gameObjName == GameObjectName::GameObject_WoodPlat || gObjB->gameObjName == GameObjectName::GameObject_Ground) )
			return 0;
	
	if( (gObjA->gameObjName == GameObjectName::GameObject_WoodPlat || gObjA->gameObjName == GameObjectName::GameObject_Ground) &&
		(gObjB->gameObjName != GameObjectName::GameObject_WoodPlat || gObjB->gameObjName != GameObjectName::GameObject_Ground) )
			return 1;

	if( (gObjA->gameObjName != GameObjectName::GameObject_WoodPlat || gObjA->gameObjName != GameObjectName::GameObject_Ground) &&
		(gObjB->gameObjName == GameObjectName::GameObject_WoodPlat || gObjB->gameObjName == GameObjectName::GameObject_Ground) )
		return -1;

	return 0;
	
}


float AngryContactListener::getTypeModifier(BlockType type)
{
	switch (type)
	{
	case BlockType::Glass:
		return 1.0f;
	case BlockType::Wood:
		return 2.0f;
	case BlockType::Stone:
		return 10.0f;
	default:
		return 1.0f;
	}
}