#ifndef PARTLIST_H
#define PARTLIST_H

#include "World.h"
#include "PixelToMeter.h"
#include <assert.h>

enum ParticlesType
{
	Splinters,
	Feathers
};
enum SplinterType
{
	WoodFrag = 1,
	StoneFrag,
	GlassFrag,
	SmokeFrag
};

struct Particle
{
	GameObjectParticle * pGameOject;
	float  life;
	Particle * pnext;

	void Initialize(b2Vec2 SpawnPosition,b2Vec2 SpawnImpulse, ParticlesType type, int splintertype = 0)
	{

		if (type == ParticlesType::Feathers)
		{
			GameSprite * pGameSprite = 0;
			switch (World::getInstance().CurrentType)
			{
			
				case RED_BIRD:
					pGameSprite= new GameSprite(SpriteBatchName::SpriteBatch_Layer1, SpriteName::Sprite_Feather, ImageName::Image_RedBirdFeather, Rect( MeterToPixel(SpawnPosition.x), MeterToPixel(SpawnPosition.y), 15, 15) );
				break;

				case BLUE_BIRD:
					pGameSprite= new GameSprite(SpriteBatchName::SpriteBatch_Layer1, SpriteName::Sprite_Feather, ImageName::Image_BlueBirdFeather, Rect( MeterToPixel(SpawnPosition.x), MeterToPixel(SpawnPosition.y), 15, 15) );
				break;

				case YELLOW_BIRD:
					pGameSprite= new GameSprite(SpriteBatchName::SpriteBatch_Layer1, SpriteName::Sprite_Feather, ImageName::Image_YellowBirdFeather, Rect( MeterToPixel(SpawnPosition.x), MeterToPixel(SpawnPosition.y), 15, 15) );
				break;

				case BLACK_BIRD:
					pGameSprite= new GameSprite(SpriteBatchName::SpriteBatch_Layer1, SpriteName::Sprite_Feather, ImageName::Image_BlackBirdFeather, Rect( MeterToPixel(SpawnPosition.x), MeterToPixel(SpawnPosition.y), 15, 15) );
				break;

				case WHITE_BIRD:
					pGameSprite= new GameSprite(SpriteBatchName::SpriteBatch_Layer1, SpriteName::Sprite_Feather, ImageName::Image_WhiteBirdFeather, Rect( MeterToPixel(SpawnPosition.x), MeterToPixel(SpawnPosition.y), 15, 15) );
				break;
				case GREEN_BIRD:
					pGameSprite= new GameSprite(SpriteBatchName::SpriteBatch_Layer1, SpriteName::Sprite_Feather, ImageName::Image_GreenBirdFeather, Rect( MeterToPixel(SpawnPosition.x), MeterToPixel(SpawnPosition.y), 15, 15) );
				break;
			 

			}
			CircleSprite *pCircle = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f,  Color(Yellow), Rect(MeterToPixel(SpawnPosition.x), MeterToPixel(SpawnPosition.y), 15, 15)) ;
			pGameOject = new GameObjectParticle(GameObjectName::GameObject_Particle, pGameSprite,pCircle);
			pGameOject->pGameSprite->enable();
		}
		else if (type == ParticlesType::Splinters)
		{
			assert(splintertype != 0);
			GameSprite * pGameSprite = 0;
			switch (splintertype)
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
			CircleSprite *pCircle = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f,  Color(Yellow), Rect(MeterToPixel(SpawnPosition.x), MeterToPixel(SpawnPosition.y), 15, 15)) ;
			pGameOject = new GameObjectParticle(GameObjectName::GameObject_Particle, pGameSprite,pCircle);
			pGameOject->pGameSprite->enable();
		}
		b2BodyDef DynamicDef;
		DynamicDef.type = b2_dynamicBody;

		DynamicDef.position.Set( SpawnPosition.x,SpawnPosition.y);
		DynamicDef.angle = 	0.0f ;
		b2Body *pDynamicBody = World::getInstance().getWorldPtr()->CreateBody(&DynamicDef);

		b2CircleShape DynamicCircle;
		DynamicCircle.m_radius = PixelToMeter(pGameOject->pCircleSprite->origWidth * 0.5f);

		b2FixtureDef DynamicFixtureDef;
		DynamicFixtureDef.shape = &DynamicCircle;
		DynamicFixtureDef.density = 1;
        DynamicFixtureDef.filter.categoryBits = _entityCategory::PARTICLE;
		DynamicFixtureDef.filter.maskBits = _entityCategory::BOUNDARY | _entityCategory::PARTICLE;
		DynamicFixtureDef.friction = 1.0f;
		DynamicFixtureDef.restitution = 0.0f;
		DynamicFixtureDef.userData = pGameOject;

		pDynamicBody->CreateFixture( &DynamicFixtureDef);
		pDynamicBody->SetActive(true);
		
		pDynamicBody->SetUserData( pGameOject);
		pGameOject->pBody = pDynamicBody;
		pGameOject->pBody->ApplyLinearImpulse( SpawnImpulse, SpawnPosition , true);
		pGameOject->pBody->ApplyTorque(0.1f, true);
		
		
		this->life = 2;
	}
};



class ParticleList
{
public:
	ParticleList(ParticlesType);
	~ParticleList(void);

	void MarkforAdd (b2Vec2);
	void Add(b2Vec2,b2Vec2, int splintertype = 0);
	void Remove(Particle *,Particle *);
	void Update();

private:
	ParticleList(void){};
	
	ParticlesType Type;

	Particle * Active;
	Particle * Reserve;
	
	Particle * CreateNewNode(b2Vec2,b2Vec2, int splintertype = 0);
	void ApplyNewData(Particle *,b2Vec2,b2Vec2, int splintertype = 0);
	void DisableParticle(Particle *);
};

#endif

