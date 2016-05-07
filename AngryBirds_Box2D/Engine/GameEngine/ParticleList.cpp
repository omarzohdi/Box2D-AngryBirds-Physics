#include "ParticleList.h"


ParticleList::ParticleList(ParticlesType Type)
{
	Active = 0;
	Reserve = 0;
	this->Type = Type;
}


void ParticleList::Add(b2Vec2 SpawnPoint, b2Vec2 SpawnImpulse , int splintertype)
{
	if (this->Reserve == 0)
	{
		Particle * newNode = this->CreateNewNode(SpawnPoint,SpawnImpulse, splintertype);
		newNode->pnext = this->Active;
		this->Active = newNode;
	}
	else
	{
		Particle * temp = this->Reserve;
		this->Reserve = this->Reserve->pnext;

		this->ApplyNewData (temp, SpawnPoint, SpawnImpulse,splintertype);

		temp->pnext = this->Active;
		this->Active = temp;
	}

}
void ParticleList::Remove(Particle * Previous,Particle * Current)
{
	this->DisableParticle(Current);

	if (Previous !=0)
	{
		Previous->pnext = Current->pnext;
		Current->pnext = this->Reserve;

		this->Reserve = Current;
	}
	else
	{
		Current->pnext = this->Reserve;
		this->Reserve = Current;
		this->Active = 0;
	}
}

void ParticleList::Update()
{
	Particle * ptrcurr = this->Active;
	Particle * ptrprev = 0;

	while ( ptrcurr != 0)
	{
		ptrcurr->life -= 0.1f;
		if (ptrcurr->life <= 0.0f)
		{
			Particle * temp = ptrcurr -> pnext;
			Remove(ptrprev, ptrcurr);
			ptrcurr = temp;
		}
		else
		{
			ptrcurr->pGameOject->pBody->SetActive(true);
			ptrprev = ptrcurr;
			ptrcurr = ptrcurr->pnext;
		}
	}
}

Particle * ParticleList::CreateNewNode(b2Vec2 SpawnPoint, b2Vec2 SpawnImpulse, int splintertype)
{
	Particle * NewNode = new Particle();
	NewNode->Initialize(SpawnPoint,SpawnImpulse, this->Type, splintertype);
	return  NewNode;
}
void ParticleList::DisableParticle(Particle * toDisable)
{
	toDisable->pGameOject->pGameSprite->disable();
	toDisable->pGameOject->pCircleSprite->disable();
	toDisable->pGameOject->pBody->SetActive(false);
	toDisable->life = 0;
}

void ParticleList::ApplyNewData(Particle * NewNode,b2Vec2 SpawnPosition,b2Vec2 SpawnImpulse, int splintertype)
{
	NewNode->pGameOject->pBody->SetActive(true);
	NewNode->pGameOject->pBody->SetTransform(SpawnPosition,0.0f);
	NewNode->pGameOject->pBody->ApplyLinearImpulse(SpawnImpulse,SpawnPosition,0.0f);
		

	NewNode->pGameOject->pGameSprite->posX = MeterToPixel(SpawnPosition.x);
	NewNode->pGameOject->pGameSprite->posY = MeterToPixel(SpawnPosition.y);
	NewNode->pGameOject->pGameSprite->enable();
	NewNode->pGameOject->pCircleSprite->enable();
	NewNode->life = 2;

	if (this->Type == ParticlesType::Splinters)
	{
		assert (splintertype != 0);
		GameSprite * pGameSprite = 0;
		switch ( splintertype )
		{
			case WoodFrag:
				pGameSprite= new GameSprite(SpriteBatchName::SpriteBatch_Layer1, SpriteName::Sprite_Feather, ImageName::Image_WoodBlockFragment, Rect( MeterToPixel(SpawnPosition.x), MeterToPixel(SpawnPosition.y), 36, 12) );
			break;

			case StoneFrag:
				pGameSprite= new GameSprite(SpriteBatchName::SpriteBatch_Layer1, SpriteName::Sprite_Feather, ImageName::Image_StoneBlockFragment, Rect( MeterToPixel(SpawnPosition.x), MeterToPixel(SpawnPosition.y), 25, 31) );
			break;

			case GlassFrag:
				pGameSprite= new GameSprite(SpriteBatchName::SpriteBatch_Layer1, SpriteName::Sprite_Feather, ImageName::Image_GlassBlockFragment, Rect( MeterToPixel(SpawnPosition.x), MeterToPixel(SpawnPosition.y), 33, 33) );
			break;

			case SmokeFrag:
				pGameSprite= new GameSprite(SpriteBatchName::SpriteBatch_Layer1, SpriteName::Sprite_Feather, ImageName::Image_SmokeFragment, Rect( MeterToPixel(SpawnPosition.x), MeterToPixel(SpawnPosition.y), 12, 12) );
			break;

		}
	}
	else 
	{
		switch(World::getInstance().CurrentType)
		{
			case RED_BIRD:
				NewNode->pGameOject->pGameSprite->spriteModel->SwapImage(ImageName::Image_RedBirdFeather );
			break;

			case BLUE_BIRD:
				NewNode->pGameOject->pGameSprite->spriteModel->SwapImage(ImageName::Image_BlueBirdFeather );
			break;

			case YELLOW_BIRD:
				NewNode->pGameOject->pGameSprite->spriteModel->SwapImage(ImageName::Image_YellowBirdFeather );
			break;

			case BLACK_BIRD:
				NewNode->pGameOject->pGameSprite->spriteModel->SwapImage(ImageName::Image_BlackBirdFeather );
			break;

			case WHITE_BIRD:
				NewNode->pGameOject->pGameSprite->spriteModel->SwapImage(ImageName::Image_WhiteBirdFeather );
			break;
			case GREEN_BIRD:
				NewNode->pGameOject->pGameSprite->spriteModel->SwapImage(ImageName::Image_GreenBirdFeather );
			break;
		}
	}
}

ParticleList::~ParticleList(void)
{

}
