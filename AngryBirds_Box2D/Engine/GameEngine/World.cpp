#include "World.h"
#include "TextMan.h"
#include "EnumName.h"
#include "Rect.h"
#include "ImageMan.h"
#include "Image.h"
#include "SpriteBatchManager.h"
#include "SpriteBatch.h"
#include "BoxSprite.h"
#include "Input.h"
#include "irrKlang.h"
#include "AngryContactListener.h"
#include "PolySprite.h"

#define STARTTIME 1.0f
static int LEVEL = 0;

#include <iostream>
#include <stdio.h>
using namespace irrklang;

bool userinput;
extern ISoundEngine	*pSndEngine;
extern ISound	*pSndTheme;
b2Vec2 EXPLOSIONPOINT;
b2Vec2 POWERPOINT;

#include "ParticleEmitter.h"

int randomVal;


World::World(void)
{
	this->velocityIterations = 6;
	this->positionIternations = 2;
	this->isfirstStep = true;
	this->starttimer = 0;
	this->removebird = false;
	this->BirdsinWorld = 0;
	this->TrailList = new Trail();
	userinput = false;

	this->FeatherEmitter = new ParticleEmitter(ParticlesType::Feathers);
	this->SplinterEmitter = new ParticleEmitter(ParticlesType::Splinters);
	this->CurrentBird = 0;
	NEWBIRD = false;

	this->Queue = new BirdType[6];

	this->Queue[0] = BirdType::RED_BIRD;
	this->Queue[1] = BirdType::BLUE_BIRD;
	this->Queue[2] = BirdType::YELLOW_BIRD;
	this->Queue[3] = BirdType::GREEN_BIRD;
	this->Queue[4] = BirdType::WHITE_BIRD;
	this->Queue[5] = BirdType::BLACK_BIRD;

	CurrentType = Queue[CurrentType];
	
	POWERPOINT.SetZero();
}

World::~World(void)
{

}

void World::initializeWorld()
{

	
	loadAssets();

	loadWorldPhysics();	
	loadWorldObjects();
}

void World::loadAssets()
{
	TextMan::Load(TextType::Text2D, TextName::Texture_Birds, "unsorted.tga");
	TextMan::Load(TextType::Text2D, TextName::Texture_WoodPlat, "woodPlatform.tga");
	TextMan::Load(TextType::Text2D, TextName::Texture_Wood_Blocks, "woodBlocks.tga" );
	TextMan::Load(TextType::Text2D, TextName::Texture_BackgroundCloud, "CloudLayer.tga");
	TextMan::Load(TextType::Text2D, TextName::Texture_BackgroundTrees, "TreeLayer.tga");
	TextMan::Load(TextType::Text2D, TextName::Texture_BackgroundGrass, "GrassBehindBirds.tga");
	TextMan::Load(TextType::Text2D, TextName::Texture_BackgroundGround, "foreground.tga");
	TextMan::Load(TextType::Text2D, TextName::Texture_Glass_Blocks, "glassBlocks.tga");
	TextMan::Load(TextType::Text2D, TextName::Texture_Stone_Blocks, "stoneBlocks.tga");

	TextMan::Load(TextType::Text2D, TextName::Texture_Stone_Blocks, "stoneBlocks.tga");
	ImageMan::Add(ImageName::Image_Ground,	TextName::Texture_Stone_Blocks, Rect(0, 0, 1, 1));

	ImageMan::Add(ImageName::Image_BackgroundCloud, TextName::Texture_BackgroundCloud, Rect(0, 0, 1280, 864) );
	ImageMan::Add(ImageName::Image_BackgroundTrees, TextName::Texture_BackgroundTrees, Rect(0, 0, 1280,846) );
	ImageMan::Add(ImageName::Image_BackgroundGrass, TextName::Texture_BackgroundGrass, Rect(0, 0, 1280,846) );
	ImageMan::Add(ImageName::Image_BackgroundGround,TextName::Texture_BackgroundGround, Rect(0, 0, 1280,846) );

	ImageMan::Add(ImageName::Image_RedBird,			TextName::Texture_Birds, Rect(903, 797, 46, 46) );
	ImageMan::Add(ImageName::Image_YellowBird,TextName::Texture_Birds, Rect(667, 878, 59, 56) );
	ImageMan::Add(ImageName::Image_BlueBird,	TextName::Texture_Birds, Rect(0, 378, 31, 32) );
	ImageMan::Add(ImageName::Image_WhiteBird, TextName::Texture_Birds, Rect(409, 352, 81, 94) );
	ImageMan::Add(ImageName::Image_GreenBird, TextName::Texture_Birds, Rect(931, 528, 100, 73) );
	ImageMan::Add(ImageName::Image_BlackBird, TextName::Texture_Birds, Rect(407, 725, 66, 84));

	ImageMan::Add(ImageName::Image_RedBirdBlink, TextName::Texture_Birds, Rect(903, 890, 53, 53) );
	ImageMan::Add(ImageName::Image_YellowBirdBlink,TextName::Texture_Birds, Rect(731, 743, 59, 56) );
	ImageMan::Add(ImageName::Image_BlueBirdBlink,  TextName::Texture_Birds, Rect(0, 507, 31, 30) );
	ImageMan::Add(ImageName::Image_WhiteBirdBlink, TextName::Texture_Birds, Rect(409, 448, 82, 94) );
	ImageMan::Add(ImageName::Image_GreenBirdBlink, TextName::Texture_Birds, Rect(668, 605, 100, 73) );
	ImageMan::Add(ImageName::Image_BlackBirdBlink, TextName::Texture_Birds, Rect(714, 445, 66, 84));

	ImageMan::Add(ImageName::Image_RedBirdFeather, TextName::Texture_Birds, Rect(1, 474, 12, 27) );
	ImageMan::Add(ImageName::Image_YellowBirdFeather,TextName::Texture_Birds, Rect(29, 442, 9, 25) );
	ImageMan::Add(ImageName::Image_BlueBirdFeather,	 TextName::Texture_Birds, Rect(28, 655, 10, 18) );
	ImageMan::Add(ImageName::Image_WhiteBirdFeather, TextName::Texture_Birds, Rect(23, 627, 12, 25) );
	ImageMan::Add(ImageName::Image_GreenBirdFeather, TextName::Texture_Birds, Rect(23, 627, 12, 25) );
	ImageMan::Add(ImageName::Image_BlackBirdFeather, TextName::Texture_Birds, Rect(16, 452, 11, 72));

	ImageMan::Add(ImageName::Image_HelmetPig,			TextName::Texture_Birds, Rect(489, 444, 102, 91) );
	ImageMan::Add(ImageName::Image_HelmetPigHurt1,		TextName::Texture_Birds, Rect(490, 528, 97, 88) );
	ImageMan::Add(ImageName::Image_HelmetPigHurt2,		TextName::Texture_Birds, Rect(489, 784, 97, 82) );

	ImageMan::Add(ImageName::Image_HelmetPigBlink,		TextName::Texture_Birds, Rect(764, 351, 96, 95) );
	ImageMan::Add(ImageName::Image_HelmetPigHurt1Blink, TextName::Texture_Birds, Rect(858, 352, 93, 90) );
	ImageMan::Add(ImageName::Image_HelmetPigHurt2Blink,	TextName::Texture_Birds, Rect(953, 352, 93, 93) );
    
	ImageMan::Add(ImageName::Image_BlueBirdHurt,	 TextName::Texture_Birds, Rect(0, 410, 31, 32) );	
	ImageMan::Add(ImageName::Image_GreenBirdSmashed, TextName::Texture_Birds, Rect(951, 604, 96, 73) );
	ImageMan::Add(ImageName::Image_WhiteBirdPoop,	 TextName::Texture_Birds, Rect(493, 352, 85, 93) );
	ImageMan::Add(ImageName::Image_YellowBirdAngry,  TextName::Texture_Birds, Rect(588, 915, 68, 54) );
	ImageMan::Add(ImageName::Image_RedBirdCaw,		 TextName::Texture_Birds, Rect(949, 798, 48, 48) );
	ImageMan::Add(ImageName::Image_WhiteEgg,		 TextName::Texture_Birds, Rect(667, 820, 46, 59) );


    ImageMan::Add(ImageName::Image_PigHurt,  TextName::Texture_Birds, Rect(297, 848, 100, 99) );
	ImageMan::Add(ImageName::Image_PigBlink,  TextName::Texture_Birds, Rect(584, 528, 81, 80) );

	ImageMan::Add(ImageName::Image_GlassBlockFragment, TextName::Name:: Texture_Birds, Rect(2, 240, 30, 34));
	ImageMan::Add(ImageName::Image_StoneBlockFragment, TextName::Name::Texture_Birds, Rect(2, 569, 34, 29));
	ImageMan::Add(ImageName::Image_WoodBlockFragment, TextName::Name::Texture_Birds, Rect(11, 848, 36, 12));
	ImageMan::Add(ImageName::Image_SmokeFragment, TextName::Name::Texture_Birds, Rect(15, 768, 12, 12));


	ImageMan::Add(ImageName::Image_WoodTriangle1, TextName::Texture_Wood_Blocks, Rect(167, 2, 82, 80));

	ImageMan::Add(ImageName::Image_SmokeRing1, TextName::Texture_Birds, Rect(167, 513, 118, 111) );

	ImageMan::Add(ImageName::Image_Pig,				TextName::Texture_Birds, Rect(297, 356, 100, 99) );

	ImageMan::Add(ImageName::Image_SlingRight,		TextName::Texture_Birds, Rect(0, 0, 40, 200));
	ImageMan::Add(ImageName::Image_SlingLeft,		TextName::Texture_Birds, Rect(832, 0, 44, 125));
	
	ImageMan::Add(ImageName::Image_woodMiniPlank_1,	TextName::Texture_Wood_Blocks, Rect(458, 256, 41, 22));
	ImageMan::Add(ImageName::Image_woodMiniPlank_2,	TextName::Texture_Wood_Blocks, Rect(458, 279, 41, 22));
	ImageMan::Add(ImageName::Image_woodMiniPlank_3,	TextName::Texture_Wood_Blocks, Rect(458, 301, 41, 22));
	ImageMan::Add(ImageName::Image_woodMiniPlank_4,	TextName::Texture_Wood_Blocks, Rect(458, 323, 41, 22));
	
	ImageMan::Add(ImageName::Image_woodPlankShort_1, TextName::Texture_Wood_Blocks, Rect(288, 344, 83, 22));
	ImageMan::Add(ImageName::Image_woodPlankShort_2, TextName::Texture_Wood_Blocks, Rect(288, 367, 83, 22));
	ImageMan::Add(ImageName::Image_woodPlankShort_3, TextName::Texture_Wood_Blocks, Rect(372, 344, 83, 22));
	ImageMan::Add(ImageName::Image_woodPlankShort_4, TextName::Texture_Wood_Blocks, Rect(372, 367, 83, 22));

	/// this is not the med but long correct later!
	ImageMan::Add(ImageName::Image_woodPlankMed_1, TextName::Texture_Wood_Blocks,Rect(288, 258, 167, 20) );
	ImageMan::Add(ImageName::Image_woodPlankMed_2, TextName::Texture_Wood_Blocks,Rect(288, 280, 167, 20) );
	ImageMan::Add(ImageName::Image_woodPlankMed_3, TextName::Texture_Wood_Blocks,Rect(288, 302, 167, 20) );
	ImageMan::Add(ImageName::Image_woodPlankMed_4, TextName::Texture_Wood_Blocks,Rect(288, 324, 167, 20) );

	ImageMan::Add(ImageName::Image_woodPlankLong_1, TextName::Texture_Wood_Blocks,Rect(288, 169, 204, 20) );
	ImageMan::Add(ImageName::Image_woodPlankLong_2, TextName::Texture_Wood_Blocks,Rect(288, 191, 204, 20) );
	ImageMan::Add(ImageName::Image_woodPlankLong_3, TextName::Texture_Wood_Blocks,Rect(288, 213, 204, 20) );
	ImageMan::Add(ImageName::Image_woodPlankLong_4, TextName::Texture_Wood_Blocks,Rect(288, 235, 204, 20) );

	ImageMan::Add(ImageName::Image_WoodBlock_1, TextName::Texture_Wood_Blocks,Rect(246, 84, 84, 40) );
	ImageMan::Add(ImageName::Image_WoodBlock_2, TextName::Texture_Wood_Blocks,Rect(332, 84, 84, 40) );
	ImageMan::Add(ImageName::Image_WoodBlock_3, TextName::Texture_Wood_Blocks,Rect(417, 84, 84, 40) );
	ImageMan::Add(ImageName::Image_WoodBlock_4, TextName::Texture_Wood_Blocks,Rect(246, 126, 84, 40) );

	ImageMan::Add(ImageName::Image_WoodCube_1, TextName::Texture_Wood_Blocks,Rect(2, 338, 40, 40) );
	ImageMan::Add(ImageName::Image_WoodCube_2, TextName::Texture_Wood_Blocks,Rect(86, 338, 40, 40) );
	ImageMan::Add(ImageName::Image_WoodCube_3, TextName::Texture_Wood_Blocks,Rect(332, 127, 40, 40) );
	ImageMan::Add(ImageName::Image_WoodCube_4, TextName::Texture_Wood_Blocks,Rect(375, 127, 40, 40) );

	ImageMan::Add(ImageName::Image_StoneBlock_1, TextName::Texture_Stone_Blocks,Rect(246, 84, 84, 40) );
	ImageMan::Add(ImageName::Image_StoneBlock_2, TextName::Texture_Stone_Blocks,Rect(332, 84, 84, 40) );
	ImageMan::Add(ImageName::Image_StoneBlock_3, TextName::Texture_Stone_Blocks,Rect(417, 84, 84, 40) );
	ImageMan::Add(ImageName::Image_StoneBlock_4, TextName::Texture_Stone_Blocks,Rect(246, 126, 84, 40) );

	ImageMan::Add(ImageName::Image_woodPlatform, TextName::Texture_WoodPlat, Rect(0, 0, 156, 44));

	ImageMan::Add(ImageName::Image_GlassPlank_1, TextName::Texture_Glass_Blocks, Rect(287, 346, 82, 22));
	ImageMan::Add(ImageName::Image_GlassPlank_2, TextName::Texture_Glass_Blocks, Rect(287, 367, 82, 22));
	ImageMan::Add(ImageName::Image_GlassPlank_3, TextName::Texture_Glass_Blocks, Rect(374, 346, 82, 22));
	ImageMan::Add(ImageName::Image_GlassPlank_4, TextName::Texture_Glass_Blocks, Rect(374, 367, 82, 22));

	
	ImageMan::Add(ImageName::Image_GlassBlock_1, TextName::Texture_Glass_Blocks, Rect(333, 84, 82, 40));
	ImageMan::Add(ImageName::Image_GlassBlock_2, TextName::Texture_Glass_Blocks, Rect(418, 84, 82, 40));
	ImageMan::Add(ImageName::Image_GlassBlock_3, TextName::Texture_Glass_Blocks, Rect(333, 128, 82, 40));
	ImageMan::Add(ImageName::Image_GlassBlock_4, TextName::Texture_Glass_Blocks, Rect(245, 128, 82, 40));

	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Debug);
	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Layer2);
	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Birds);
	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Blocks);
	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Trail);
	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Layer1);
	SpriteBatchManager::AddBatch(SpriteBatchName::SpriteBatch_Background);
	
}

void World::GeneratePlatformPhysicsBody(GameObjectPlatform * inObject)
{
	b2BodyDef StaticBodyDef;
	StaticBodyDef.type = b2_staticBody;

	StaticBodyDef.position.Set( PixelToMeter(inObject->pBoxSprite->posX),PixelToMeter(inObject->pBoxSprite->posY));
	StaticBodyDef.angle = 	3.14f ;
	b2Body *pStaticBody = this->pWorld->CreateBody(&StaticBodyDef);
		
	b2PolygonShape PlatformBox;

	PlatformBox.SetAsBox( PixelToMeter(inObject->pBoxSprite->origWidth * 0.5f), PixelToMeter(inObject->pBoxSprite->origHeight * 0.5f) );
		
	b2FixtureDef StaticFixtureDef;
	StaticFixtureDef.shape = &PlatformBox;
	StaticFixtureDef.filter.categoryBits = _entityCategory::BOUNDARY;
	StaticFixtureDef.filter.maskBits = _entityCategory::BIRD | _entityCategory::PIG | _entityCategory::PARTICLE | _entityCategory::BLOCK;

	pStaticBody->CreateFixture(&StaticFixtureDef);
	pStaticBody->GetFixtureList()->SetUserData(inObject);
	pStaticBody->SetActive(false);

	pStaticBody->SetUserData( inObject);	
	inObject->pBody = pStaticBody;
}
void World::GenerateBirdPhysicsBody(GameObjectBird * inObject)
{
	b2BodyDef DynamicDef;
	DynamicDef.type = b2_dynamicBody;

	DynamicDef.position.Set( PixelToMeter(inObject->pCircleSprite->posX),PixelToMeter(inObject->pCircleSprite->posY));
	DynamicDef.angle = 	0.0f ;
	b2Body *pDynamicBody = this->pWorld->CreateBody(&DynamicDef);
		

	b2CircleShape DynamicCircle;
	DynamicCircle.m_radius = PixelToMeter(inObject->pCircleSprite->origWidth * 0.5f);

	b2FixtureDef DynamicFixtureDef;
	DynamicFixtureDef.shape = &DynamicCircle;
	DynamicFixtureDef.density = 10.0f;
	DynamicFixtureDef.filter.categoryBits = _entityCategory::BIRD;
	DynamicFixtureDef.filter.maskBits = _entityCategory::PIG | _entityCategory::BOUNDARY | _entityCategory::BLOCK ;
	DynamicFixtureDef.friction = 1.0f;
	DynamicFixtureDef.restitution = 0.50f;
	DynamicFixtureDef.userData = inObject;

	pDynamicBody->CreateFixture( &DynamicFixtureDef);
	pDynamicBody->SetActive(false);

	pDynamicBody->SetUserData( inObject);
	inObject->pBody = pDynamicBody;
}
void World::GenerateEggPhysicsBody(GameObjectEgg * inObject)
{
	b2BodyDef DynamicDef;
	DynamicDef.type = b2_dynamicBody;

	DynamicDef.position.Set( PixelToMeter(inObject->pCircleSprite->posX),PixelToMeter(inObject->pCircleSprite->posY));
	DynamicDef.angle = 	0.0f ;
	b2Body *pDynamicBody = this->pWorld->CreateBody(&DynamicDef);
		

	b2CircleShape DynamicCircle;
	DynamicCircle.m_radius = PixelToMeter(inObject->pCircleSprite->origWidth * 0.5f);

	b2FixtureDef DynamicFixtureDef;
	DynamicFixtureDef.shape = &DynamicCircle;
	DynamicFixtureDef.density = 10.0f;
	DynamicFixtureDef.filter.categoryBits = _entityCategory::BIRD;
	DynamicFixtureDef.filter.maskBits = _entityCategory::PIG | _entityCategory::BOUNDARY | _entityCategory::BLOCK ;
	DynamicFixtureDef.friction = 1.0f;
	DynamicFixtureDef.restitution = 0.50f;
	DynamicFixtureDef.userData = inObject;

	pDynamicBody->CreateFixture( &DynamicFixtureDef);
	pDynamicBody->SetActive(false);

	pDynamicBody->SetUserData( inObject);
	inObject->pBody = pDynamicBody;
}
void World::GeneratePigPhysicsBody(GameObjectPig * inObject)
{
	b2BodyDef DynamicDef;
	DynamicDef.type = b2_dynamicBody;

	DynamicDef.position.Set( PixelToMeter(inObject->pCircleSprite->posX),PixelToMeter(inObject->pCircleSprite->posY));
	DynamicDef.angle = 	0.0f ;
	b2Body *pDynamicBody = this->pWorld->CreateBody(&DynamicDef);
		

	b2CircleShape DynamicCircle;
	DynamicCircle.m_radius = PixelToMeter(inObject->pCircleSprite->origWidth * 0.5f);

	b2FixtureDef DynamicFixtureDef;
	DynamicFixtureDef.shape = &DynamicCircle;
	DynamicFixtureDef.density = 2.0f;
	DynamicFixtureDef.filter.categoryBits = _entityCategory::PIG;
	DynamicFixtureDef.filter.maskBits = _entityCategory::BIRD | _entityCategory::BLOCK | _entityCategory::BOUNDARY | _entityCategory::PIG;
	DynamicFixtureDef.friction = 0.3f;
	DynamicFixtureDef.restitution = 0.50f;
	DynamicFixtureDef.userData = inObject;

	pDynamicBody->CreateFixture( &DynamicFixtureDef);
	pDynamicBody->SetActive(false);

	pDynamicBody->SetUserData( inObject);
	inObject->pBody = pDynamicBody;
}
void World::GenerateBlockPhysicsBody(GameObjectBlock * inObject, float rotation)
{
	b2BodyDef DynamicDef;
	DynamicDef.type = b2_dynamicBody;

	DynamicDef.position.Set( PixelToMeter(inObject->pBoxSprite->posX),PixelToMeter(inObject->pBoxSprite->posY ));
	DynamicDef.angle = 	rotation ;
	b2Body *pDynamicBody = this->pWorld->CreateBody(&DynamicDef);
		
	b2PolygonShape DynamicBox;

	DynamicBox.SetAsBox( PixelToMeter(inObject->pBoxSprite->origWidth * 0.5f), PixelToMeter(inObject->pBoxSprite->origHeight * 0.5f));
		
	b2FixtureDef DynamicFixtureDef;
	DynamicFixtureDef.shape = &DynamicBox;
	DynamicFixtureDef.filter.categoryBits = _entityCategory::BLOCK;
	DynamicFixtureDef.filter.maskBits = _entityCategory::BIRD | _entityCategory::PIG | _entityCategory::BOUNDARY | _entityCategory::BLOCK;

	if (inObject->gameObjName == GameObjectName::GameObject_Block)
	{
		DynamicFixtureDef.density = 3.0f;
		DynamicFixtureDef.friction = 0.3f;
		DynamicFixtureDef.restitution = 0.50f;
	}
	if (inObject->gameObjName == GameObjectName::GameObject_Glass_Block)
	{
		DynamicFixtureDef.density = 1.0f;
		DynamicFixtureDef.friction = 0.3f;
		DynamicFixtureDef.restitution = 0.50f;
	}
	if (inObject->gameObjName == GameObjectName::GameObject_Stone_Block)
	{
		DynamicFixtureDef.density = 5.0f;
		DynamicFixtureDef.friction = 100.0f;
		DynamicFixtureDef.restitution = 0.50f;
	}
	
	DynamicFixtureDef.userData = inObject;

	pDynamicBody->CreateFixture( &DynamicFixtureDef);
	pDynamicBody->SetActive(false);

	pDynamicBody->SetUserData( inObject);
	inObject->pBody = pDynamicBody;
}
void World::GenerateBlockPhysicsBodyRound(GameObjectBlockRound * inObject)
{
	b2BodyDef DynamicDef;
	DynamicDef.type = b2_dynamicBody;

	DynamicDef.position.Set( PixelToMeter(inObject->pCircleSprite->posX),PixelToMeter(inObject->pCircleSprite->posY ));
	DynamicDef.angle = 	0.0f ;
	b2Body *pDynamicBody = this->pWorld->CreateBody(&DynamicDef);

	b2CircleShape DynamicCircle;
	DynamicCircle.m_radius = PixelToMeter(inObject->pCircleSprite->origWidth * 0.5f);
		
	b2FixtureDef DynamicFixtureDef;
	DynamicFixtureDef.shape = &DynamicCircle;
	DynamicFixtureDef.filter.categoryBits = _entityCategory::BLOCK;
	DynamicFixtureDef.filter.maskBits = _entityCategory::BIRD | _entityCategory::PIG | _entityCategory::BOUNDARY | _entityCategory::BLOCK;

	if (inObject->gameObjName == GameObjectName::GameObject_Block)
	{
		DynamicFixtureDef.density = 3.0f;
		DynamicFixtureDef.friction = 0.3f;
		DynamicFixtureDef.restitution = 0.50f;
	}
	if (inObject->gameObjName == GameObjectName::GameObject_Glass_Block)
	{
		DynamicFixtureDef.density = 1.0f;
		DynamicFixtureDef.friction = 0.3f;
		DynamicFixtureDef.restitution = 0.50f;
	}
	if (inObject->gameObjName == GameObjectName::GameObject_Stone_Block)
	{
		DynamicFixtureDef.density = 5.0f;
		DynamicFixtureDef.friction = 100.0f;
		DynamicFixtureDef.restitution = 0.50f;
	}
	
	DynamicFixtureDef.userData = inObject;

	pDynamicBody->CreateFixture( &DynamicFixtureDef);
	pDynamicBody->SetActive(false);

	pDynamicBody->SetUserData( inObject);
	inObject->pBody = pDynamicBody;
}
void World::GenerateBlockPhysicsBodyTriangle(GameObjectBlockTriangle * inObject, float rotation)
{
	b2BodyDef DynamicDef;
	DynamicDef.type = b2_dynamicBody;

	DynamicDef.position.Set( PixelToMeter(inObject->pPolySprite->posX),PixelToMeter(inObject->pPolySprite->posY ));
	DynamicDef.angle = 	rotation ;
	b2Body *pDynamicBody = this->pWorld->CreateBody(&DynamicDef);

	b2PolygonShape DynamicTriangle;

	b2Vec2 vertices[3];

	float hw = PixelToMeter (inObject->pGameSprite->origWidth /2);
	float hh = PixelToMeter (inObject->pGameSprite->origHeight/2);

	vertices[0].Set(-hw, -hh);
	vertices[1].Set(hw, -hh);
	vertices[2].Set(-hw, hh);

	DynamicTriangle.Set(vertices, 3);
		
	b2FixtureDef DynamicFixtureDef;
	DynamicFixtureDef.shape = &DynamicTriangle;
	DynamicFixtureDef.filter.categoryBits = _entityCategory::BLOCK;
	DynamicFixtureDef.filter.maskBits = _entityCategory::BIRD | _entityCategory::PIG | _entityCategory::BOUNDARY | _entityCategory::BLOCK;

	if (inObject->gameObjName == GameObjectName::GameObject_Block)
	{
		DynamicFixtureDef.density = 3.0f;
		DynamicFixtureDef.friction = 0.3f;
		DynamicFixtureDef.restitution = 0.50f;
	}
	if (inObject->gameObjName == GameObjectName::GameObject_Glass_Block)
	{
		DynamicFixtureDef.density = 1.0f;
		DynamicFixtureDef.friction = 0.3f;
		DynamicFixtureDef.restitution = 0.50f;
	}
	if (inObject->gameObjName == GameObjectName::GameObject_Stone_Block)
	{
		DynamicFixtureDef.density = 5.0f;
		DynamicFixtureDef.friction = 100.0f;
		DynamicFixtureDef.restitution = 0.50f;
	}
	
	DynamicFixtureDef.userData = inObject;

	pDynamicBody->CreateFixture( &DynamicFixtureDef);
	pDynamicBody->SetActive(false);

	pDynamicBody->SetUserData( inObject);
	inObject->pBody = pDynamicBody;
}
void World::GenerateSlingShotPhysicsBody(GameObjectSlingshot * inObject)
{
	b2BodyDef StaticBodyDef;
	StaticBodyDef.type = b2_staticBody;

	StaticBodyDef.position.Set( PixelToMeter(inObject->pBoxSprite->posX),PixelToMeter(inObject->pBoxSprite->posY));
	StaticBodyDef.angle = 	0.0f ;
	b2Body *pStaticBody = this->pWorld->CreateBody(&StaticBodyDef);
		
	b2PolygonShape PlatformBox;

	PlatformBox.SetAsBox( PixelToMeter(inObject->pBoxSprite->origWidth * 0.5f), PixelToMeter(inObject->pBoxSprite->origHeight * 0.5f) );

	b2FixtureDef StaticFixtureDef;
	StaticFixtureDef.shape = &PlatformBox;
	StaticFixtureDef.filter.categoryBits = _entityCategory::BOUNDARY;
	StaticFixtureDef.filter.maskBits = _entityCategory::BIRD | _entityCategory::PIG | _entityCategory::PARTICLE | _entityCategory::BLOCK;

	pStaticBody->CreateFixture(&StaticFixtureDef);
	pStaticBody->GetFixtureList()->SetUserData(inObject);

	pStaticBody->SetUserData( inObject);	
	pStaticBody->SetActive(false);
	inObject->pBody = pStaticBody;
}

void World::loadWorldObjects()
{	
	///ToDo Add user Data to object


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GameSprite * SlingRightSprite = new GameSprite (SpriteBatchName::SpriteBatch_Layer1, SpriteName::Sprite_SlingRight, ImageName::Image_SlingRight, Rect(150, 230, 40, 100) );
	BoxSprite * SlingRightBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f, Vect(255,255,0,255), Rect(143, 206, 20, 50) );
	GameSprite * SlingLeftSprite =  new GameSprite (SpriteBatchName::SpriteBatch_Layer2, SpriteName::Sprite_SlingLeft, ImageName::Image_SlingLeft, Rect(127, 250, 35, 60) );
	GameObjectSlingshot * SligShotObj = new GameObjectSlingshot(GameObjectName::GameObject_WoodPlat,SlingRightSprite, SlingLeftSprite,SlingRightBox);
	GenerateSlingShotPhysicsBody(SligShotObj);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////  Create Birds  //////////////////////////////////////////////////////////////////////////////

	GameSprite *pBirdSprite1 = 	new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_Red, ImageName::Image_RedBird,		Rect(143, 270, 30, 30)	);
	GameSprite *pBirdSprite2 = new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_Yellow, ImageName::Image_YellowBird,	Rect(170, 200, 35, 35)  );
	GameSprite *pBirdSprite3 = new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_Blue, ImageName::Image_BlueBird,		Rect(220, 200, 25, 25)	);
	GameSprite *pBirdSprite4 = 	new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_Green, ImageName::Image_GreenBird,	Rect(270, 200, 35, 35)	);
	GameSprite *pBirdSprite5 = new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_White, ImageName::Image_WhiteBird,	Rect(310, 200, 35, 35)  );
	GameSprite *pBirdSprite6 = new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_Black, ImageName::Image_BlackBird,	Rect(360, 200, 35, 35)	);

	CircleSprite *pBirdCircle1 = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f,  Color(Yellow),	Rect(143, 270, 30, 30)	);
	CircleSprite *pBirdCircle2 = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f,  Color(Yellow),	Rect(170, 200, 35, 35)	);
	CircleSprite *pBirdCircle3 = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f,  Color(Yellow),	Rect(220, 200, 25, 25)  );
	CircleSprite *pBirdCircle4 = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f,  Color(Yellow),	Rect(270, 200, 35, 35)	);
	CircleSprite *pBirdCircle5 = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f,  Color(Yellow),	Rect(310, 200, 35, 35)	);
	CircleSprite *pBirdCircle6 = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f,  Color(Yellow),	Rect(360, 200, 35, 35)  );

	GameObjectBird *pBird1 = new GameObjectBird(GameObjectName::GameObject_Bird, pBirdSprite1, pBirdCircle1, this->Queue[0]);
	GameObjectBird *pBird2 = new GameObjectBird(GameObjectName::GameObject_Bird, pBirdSprite2, pBirdCircle2, this->Queue[2]);
	GameObjectBird *pBird3 = new GameObjectBird(GameObjectName::GameObject_Bird, pBirdSprite3, pBirdCircle3, this->Queue[1]);
	GameObjectBird *pBird4 = new GameObjectBird(GameObjectName::GameObject_Bird, pBirdSprite4, pBirdCircle4, this->Queue[3]);
	GameObjectBird *pBird5 = new GameObjectBird(GameObjectName::GameObject_Bird, pBirdSprite5, pBirdCircle5, this->Queue[4]);
	GameObjectBird *pBird6 = new GameObjectBird(GameObjectName::GameObject_Bird, pBirdSprite6, pBirdCircle6, this->Queue[5]);

	GenerateBirdPhysicsBody(pBird1);
	GenerateBirdPhysicsBody(pBird2);
	GenerateBirdPhysicsBody(pBird3);
	GenerateBirdPhysicsBody(pBird4);
	GenerateBirdPhysicsBody(pBird5);
	GenerateBirdPhysicsBody(pBird6);

	pBird1->pBody->SetActive(false);
	pBird2->pBody->SetActive(false);
	pBird3->pBody->SetActive(false);
	pBird4->pBody->SetActive(false);
	pBird5->pBody->SetActive(false);
	pBird6->pBody->SetActive(false);

	pBird1->active = true;
	pBird1->state = NORMAL;

	if (LEVEL == 0)
	{
	///////////////////////////////////////////////////////////////////////Building The Platfroms////////////////////////////////////////////////////////////////
	GameSprite * WoodPlat1 = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlatform1,	 ImageName::Image_woodPlatform,   Rect(1000, 200, 200, 44));
	BoxSprite *WoodPlatBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f, Vect(255,255,0,255), WoodPlat1 );
	GameObjectPlatform * WoodPlatGObj = new GameObjectPlatform(GameObjectName::GameObject_WoodPlat, WoodPlat1,WoodPlatBox);
	GeneratePlatformPhysicsBody(WoodPlatGObj);

	GameSprite * WoodPlat2  = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlatform2,	 ImageName::Image_woodPlatform,   Rect(800, 200, 200, 44));
	BoxSprite *WoodPlatBox2 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f, Vect(255,255,0,255), Rect(	800, 200, 200, 44) );
	GameObjectPlatform* WoodPlatGObj2 = new GameObjectPlatform(GameObjectName::GameObject_WoodPlat, WoodPlat2,WoodPlatBox2);
	GeneratePlatformPhysicsBody(WoodPlatGObj2);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////Building The Level////////////////////////////////////////////////////////////////////////////////////
	GameSprite *pMiniPlankRightSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodMiniPlank1,  ImageName::Image_woodMiniPlank_1,  Rect(710, 242, 40, 22));
	BoxSprite *pMiniBoxRight = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodMiniPlank1, 2.0f, Vect(255,255,0,255),  pMiniPlankRightSprite) ;
	GameObjectBlock *pMiniPlankRight = new GameObjectBlock(GameObjectName::GameObject_Block, pMiniPlankRightSprite, pMiniBoxRight, BlockType::Wood);
	GenerateBlockPhysicsBody(pMiniPlankRight, 3.14f/2.0f);
	       
	GameSprite *pMiniPlankLeftSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodMiniPlank2,	 ImageName::Image_woodMiniPlank_1,  Rect(1090, 242, 40, 22));
	BoxSprite *pMiniBoxLeft = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodMiniPlank2, 2.0f, Vect(255,255,0,255), pMiniPlankLeftSprite ) ;
	GameObjectBlock *pMiniPlankLeft = new GameObjectBlock(GameObjectName::GameObject_Block, pMiniPlankLeftSprite, pMiniBoxLeft, BlockType::Wood);
	GenerateBlockPhysicsBody(pMiniPlankLeft, 3.14f/2.0f);

	GameSprite	*pMidPlankBottomSprite =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(900, 234, 83, 22));
	BoxSprite	*MidBoxBottom = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255),  pMidPlankBottomSprite) ;
	GameObjectBlock	*pMidPlankBottom = new GameObjectBlock(GameObjectName::GameObject_Block, pMidPlankBottomSprite, MidBoxBottom , BlockType::Wood);
	GenerateBlockPhysicsBody(pMidPlankBottom);

	GameSprite	*pGlassBlockLeftSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks,  SpriteName::Sprite_GlassPlank , ImageName::Image_GlassPlank_1, Rect(870, 285, 83, 22) );
	BoxSprite	*GlassBoxLeft = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_GlassPlank, 2.0f, Vect(255,255,0,255),  pGlassBlockLeftSprite) ;
	GameObjectBlock	*pGlassBlockLeft = new GameObjectBlock(GameObjectName::GameObject_Block, pGlassBlockLeftSprite, GlassBoxLeft , BlockType::Glass);
	GenerateBlockPhysicsBody(pGlassBlockLeft, 3.14f/2.0f);

	GameSprite	*pGlassBlockRightSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks,  SpriteName::Sprite_GlassPlank, ImageName::Image_GlassPlank_1, Rect(930, 285, 83, 22) );
	BoxSprite	*RightBoxRight = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_GlassPlank, 2.0f, Vect(255,255,0,255), pGlassBlockRightSprite) ;
	GameObjectBlock	*pGlassBlockRight = new GameObjectBlock(GameObjectName::GameObject_Block, pGlassBlockRightSprite, RightBoxRight, BlockType::Glass);
	GenerateBlockPhysicsBody(pGlassBlockRight, 3.14f/2.0f);

	GameSprite	*pMidPlankMidSprite =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(900, 339, 83, 22));
	BoxSprite	*MidBoxMid = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), pMidPlankMidSprite) ;
	GameObjectBlock	*pMidPlankMid = new GameObjectBlock(GameObjectName::GameObject_Block, pMidPlankMidSprite, MidBoxMid , BlockType::Wood);
	GenerateBlockPhysicsBody(pMidPlankMid);

	GameSprite	*pLargePlankRightSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankMed1, ImageName::Image_woodPlankMed_1,   Rect(970, 306, 168, 20));
	BoxSprite	*LargeBoxRight = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankMed1, 2.0f, Vect(255,255,0,255),  pLargePlankRightSprite) ;
	GameObjectBlock	*pLargePlankRight = new GameObjectBlock(GameObjectName::GameObject_Block, pLargePlankRightSprite, LargeBoxRight , BlockType::Wood);
	GenerateBlockPhysicsBody(pLargePlankRight, 3.14f/2.0f);

	GameSprite	*pLargePlankLeftSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankMed2,	 ImageName::Image_woodPlankMed_1,   Rect(830, 306, 168, 20));
	BoxSprite	*LargeBoxLeft = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankMed2, 2.0f, Vect(255,255,0,255),  pLargePlankLeftSprite) ;
	GameObjectBlock	*pLargePlankLeft = new GameObjectBlock(GameObjectName::GameObject_Block, pLargePlankLeftSprite, LargeBoxLeft , BlockType::Wood);
	GenerateBlockPhysicsBody(pLargePlankLeft, 3.14f/2.0f);

	GameSprite	*pLargePlankMidSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankMed3,	 ImageName::Image_woodPlankMed_1,   Rect(900, 400, 168, 20));
	BoxSprite	*LargeBoxMid = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankMed3, 2.0f, Vect(255,255,0,255),  pLargePlankMidSprite) ;
	GameObjectBlock	*pLargePlankMid = new GameObjectBlock(GameObjectName::GameObject_Block, pLargePlankMidSprite, LargeBoxMid , BlockType::Wood);
	GenerateBlockPhysicsBody(pLargePlankMid);

	GameSprite	*pMiniPlankMidSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodMiniPlank4,	 ImageName::Image_woodMiniPlank_1,  Rect(900, 422, 40, 22));
	BoxSprite	*MiniBoxMid = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodMiniPlank4, 2.0f, Vect(255,255,0,255),  pMiniPlankMidSprite) ;
	GameObjectBlock	*pMiniPlankMid = new GameObjectBlock(GameObjectName::GameObject_Block, pMiniPlankMidSprite, MiniBoxMid , BlockType::Wood);
	GenerateBlockPhysicsBody(pMiniPlankMid);

	GameSprite	*pLargePlankTopRightSprite =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankMed4,	 ImageName::Image_woodPlankMed_1,   Rect(945, 495, 168, 20));
	BoxSprite	*LargeBoxTopRight = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankMed4, 2.0f, Vect(255,255,0,255),  pLargePlankTopRightSprite) ;
	GameObjectBlock	*pLargePlankTopRight = new GameObjectBlock(GameObjectName::GameObject_Block, pLargePlankTopRightSprite, LargeBoxTopRight , BlockType::Wood);
	GenerateBlockPhysicsBody(pLargePlankTopRight, 3.14f/2.0f);

	GameSprite	*pLargePlankTopLeftSprite =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankMed5,	 ImageName::Image_woodPlankMed_1,   Rect(855, 495, 168, 20));
	BoxSprite	*LargeBoxTopLeft = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankMed5, 2.0f, Vect(255,255,0,255),  pLargePlankTopLeftSprite) ;
	GameObjectBlock	*pLargePlankTopLeft = new GameObjectBlock(GameObjectName::GameObject_Block, pLargePlankTopLeftSprite, LargeBoxTopLeft , BlockType::Wood);
	GenerateBlockPhysicsBody(pLargePlankTopLeft, 3.14f/2.0f);

	GameSprite  *pMidPlankTopSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort2, ImageName::Image_woodPlankShort_1, Rect(900, 590, 83, 22));
	BoxSprite	*MidBoxTop = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort2, 2.0f, Vect(255,255,0,255),   pMidPlankTopSprite) ;
	GameObjectBlock	*pMidPlankTop = new GameObjectBlock(GameObjectName::GameObject_Block, pMidPlankTopSprite, MidBoxTop , BlockType::Wood);
	GenerateBlockPhysicsBody(pMidPlankTop);

	GameSprite	*pMiniPlankTopSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodMiniPlank3,	 ImageName::Image_woodMiniPlank_1,   Rect(900, 622, 40, 22));
	BoxSprite	*MiniBoxTop = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodMiniPlank3, 2.0f, Vect(255,255,0,255),   pMiniPlankTopSprite) ;
	GameObjectBlock	*pMiniPlankTop = new GameObjectBlock(GameObjectName::GameObject_Block, pMiniPlankTopSprite, MiniBoxTop , BlockType::Wood);
	GenerateBlockPhysicsBody(pMiniPlankTop, 3.14f/2.0f);

	///////////////////////////////////////////////////////////////////////ADD Enemies to LEVEL//////////////////////////////////////////////////////////////////////////////////////////////
	GameSprite	*pPigSprite = new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_Pig1,	ImageName::Image_Pig, Rect(900, 458, 50, 50) );
	CircleSprite	*PigCircle = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Pig1, 2.0f, Vect(255,255,0,255),  Rect(900, 458, 50, 50)) ;
	GameObjectPig	*pPig = new GameObjectPig(GameObjectName::GameObject_Pig, pPigSprite, PigCircle );
	GeneratePigPhysicsBody(pPig);
	}

	if (LEVEL == 1)
	{

	GameSprite * BaseBlocksSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_StoneBlock,	 ImageName::Image_StoneBlock_1,   Rect(750, 203, 84, 40));
	BoxSprite * BaseBlockLeftBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_StoneBlock, 2.0f, Vect(255,255,0,255), BaseBlocksSprite );
	GameObjectBlock * BaseBlockLeft = new GameObjectBlock(GameObjectName::GameObject_Block, BaseBlocksSprite,BaseBlockLeftBox, BlockType::Stone);
	GenerateBlockPhysicsBody(BaseBlockLeft);

	GameSprite * BaseBlocksSprite2 = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_StoneBlock,	 ImageName::Image_StoneBlock_1,   Rect(834, 203, 84, 40));
	BoxSprite * BaseBlockLeftBox2 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_StoneBlock, 2.0f, Vect(255,255,0,255), BaseBlocksSprite2 );
	GameObjectBlock * BaseBlockLeft2 = new GameObjectBlock(GameObjectName::GameObject_Block, BaseBlocksSprite2,BaseBlockLeftBox2, BlockType::Stone);
	GenerateBlockPhysicsBody(BaseBlockLeft2);


	GameSprite * WoodCubeSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodCube,	ImageName::Image_WoodCube_1,   Rect(750, 284, 40, 40));
	BoxSprite * WoodCubRightBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodCube, 2.0f, Vect(255,255,0,255), WoodCubeSprite );
	GameObjectBlock * WoodCubeRight = new GameObjectBlock(GameObjectName::GameObject_Block, WoodCubeSprite,WoodCubRightBox, BlockType::Wood);
	GenerateBlockPhysicsBody(WoodCubeRight);

	GameSprite * WoodBlockSprite2 = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodCube,	ImageName::Image_WoodBlock_1,   Rect(812, 284, 84, 40));
	BoxSprite * WoodBlockRightBox2 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodCube, 2.0f, Vect(255,255,0,255), WoodBlockSprite2 );
	GameObjectBlock * WoodBlockRight2 = new GameObjectBlock(GameObjectName::GameObject_Block, WoodBlockSprite2,WoodBlockRightBox2, BlockType::Wood);
	GenerateBlockPhysicsBody(WoodBlockRight2);

	GameSprite * WoodBlockSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodCube,	ImageName::Image_WoodBlock_1,   Rect(770, 245, 84, 40));
	BoxSprite * WoodBlockRightBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodCube, 2.0f, Vect(255,255,0,255), WoodBlockSprite );
	GameObjectBlock * WoodBlockRight = new GameObjectBlock(GameObjectName::GameObject_Block, WoodBlockSprite,WoodBlockRightBox, BlockType::Wood);
	GenerateBlockPhysicsBody(WoodBlockRight);

	GameSprite * WoodCubeSprite2 = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodCube,	ImageName::Image_WoodCube_1,   Rect(832, 245, 40, 40));
	BoxSprite * WoodCubRightBox2 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodCube, 2.0f, Vect(255,255,0,255), WoodCubeSprite2 );
	GameObjectBlock * WoodCubeRight2 = new GameObjectBlock(GameObjectName::GameObject_Block, WoodCubeSprite2,WoodCubRightBox2, BlockType::Wood);
	GenerateBlockPhysicsBody(WoodCubeRight2);

	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	GameSprite	*MidPlank =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(937, 235, 169, 22));
	BoxSprite	*MidplankBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), MidPlank) ;
	GameObjectBlock	*pMidPlank = new GameObjectBlock(GameObjectName::GameObject_Block, MidPlank, MidplankBox , BlockType::Wood);
	GenerateBlockPhysicsBody(pMidPlank);

	GameSprite	*pPigSpriteM = new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_Pig1,	ImageName::Image_Pig, Rect(937, 280, 70, 70) );
	CircleSprite	*PigCircleM = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Pig1, 2.0f, Vect(255,255,0,255),  Rect(937, 280, 70, 70)) ;
	GameObjectPig	*pPigM = new GameObjectPig(GameObjectName::GameObject_Pig, pPigSpriteM, PigCircleM );
	GeneratePigPhysicsBody(pPigM);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	GameSprite * BaseBlocksSprite3 = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_StoneBlock,	 ImageName::Image_StoneBlock_1,   Rect(1034, 203, 84, 40));
	BoxSprite * BaseBlockRightBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_StoneBlock, 2.0f, Vect(255,255,0,255), BaseBlocksSprite3 );
	GameObjectBlock * BaseBlockRight = new GameObjectBlock(GameObjectName::GameObject_Block, BaseBlocksSprite3,BaseBlockRightBox, BlockType::Stone);
	GenerateBlockPhysicsBody(BaseBlockRight);

	GameSprite * BaseBlocksSprite4 = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_StoneBlock,	 ImageName::Image_StoneBlock_1,   Rect(1116, 203, 84, 40));
	BoxSprite * BaseBlockRightBox2 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_StoneBlock, 2.0f, Vect(255,255,0,255), BaseBlocksSprite4 );
	GameObjectBlock * BaseBlockRight2 = new GameObjectBlock(GameObjectName::GameObject_Block, BaseBlocksSprite4,BaseBlockRightBox2, BlockType::Stone);
	GenerateBlockPhysicsBody(BaseBlockRight2);

	GameSprite * WoodCubeSpriteR = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodCube,	ImageName::Image_WoodCube_1,   Rect(1044, 284, 40, 40));
	BoxSprite * WoodCubRightBoxR = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodCube, 2.0f, Vect(255,255,0,255), WoodCubeSpriteR );
	GameObjectBlock * WoodCubeRightR = new GameObjectBlock(GameObjectName::GameObject_Block, WoodCubeSpriteR,WoodCubRightBoxR, BlockType::Wood);
	GenerateBlockPhysicsBody(WoodCubeRightR);

	GameSprite * WoodBlockSprite2R = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodCube,	ImageName::Image_WoodBlock_1,   Rect(1108, 284, 84, 40));
	BoxSprite * WoodBlockRightBox2R = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodCube, 2.0f, Vect(255,255,0,255), WoodBlockSprite2R );
	GameObjectBlock * WoodBlockRight2R = new GameObjectBlock(GameObjectName::GameObject_Block, WoodBlockSprite2R,WoodBlockRightBox2R, BlockType::Wood);
	GenerateBlockPhysicsBody(WoodBlockRight2R);

	GameSprite * WoodBlockSpriteR = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodCube,	ImageName::Image_WoodBlock_1,   Rect(1064, 245, 84, 40));
	BoxSprite * WoodBlockRightBoxR = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodCube, 2.0f, Vect(255,255,0,255), WoodBlockSpriteR );
	GameObjectBlock * WoodBlockRightR = new GameObjectBlock(GameObjectName::GameObject_Block, WoodBlockSpriteR,WoodBlockRightBoxR, BlockType::Wood);
	GenerateBlockPhysicsBody(WoodBlockRightR);

	GameSprite * WoodCubeSprite2R = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodCube,	ImageName::Image_WoodCube_1,   Rect(1126, 245, 40, 40));
	BoxSprite * WoodCubRightBox2R = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodCube, 2.0f, Vect(255,255,0,255), WoodCubeSprite2R);
	GameObjectBlock * WoodCubeRight2R = new GameObjectBlock(GameObjectName::GameObject_Block, WoodCubeSprite2R,WoodCubRightBox2R, BlockType::Wood);
	GenerateBlockPhysicsBody(WoodCubeRight2R);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
	GameSprite * StonePillar = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_StoneBlock,	 ImageName::Image_StoneBlock_1,   Rect(792, 344, 84, 40));
	BoxSprite * StonePillarBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_StoneBlock, 2.0f, Vect(255,255,0,255), StonePillar );
	GameObjectBlock * StonePillarLeft = new GameObjectBlock(GameObjectName::GameObject_Block, StonePillar,StonePillarBox, BlockType::Stone);
	GenerateBlockPhysicsBody(StonePillarLeft,3.14f/2.0f);

	GameSprite	*WoodPillarleft1 =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(740, 344, 83, 22));
	BoxSprite	*WoodPillarleft1box = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), WoodPillarleft1) ;
	GameObjectBlock	*pWoodPillarleft1 = new GameObjectBlock(GameObjectName::GameObject_Block, WoodPillarleft1, WoodPillarleft1box , BlockType::Wood);
	GenerateBlockPhysicsBody(pWoodPillarleft1,3.14f/2.0f);
	
	GameSprite	*WoodPillarleft2 =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(846, 344, 83, 22));
	BoxSprite	*WoodPillarleft2box = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), WoodPillarleft2) ;
	GameObjectBlock	*pWoodPillarleft2 = new GameObjectBlock(GameObjectName::GameObject_Block, WoodPillarleft2, WoodPillarleft2box , BlockType::Wood);
	GenerateBlockPhysicsBody(pWoodPillarleft2,3.14f/2.0f);

	GameSprite	*leftlowplank =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(792, 397, 169, 22));
	BoxSprite	*leftlowplankBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), leftlowplank) ;
	GameObjectBlock	*pleftlowplank = new GameObjectBlock(GameObjectName::GameObject_Block, leftlowplank, leftlowplankBox , BlockType::Wood);
	GenerateBlockPhysicsBody(pleftlowplank);

	GameSprite * PillarWoodBlocksSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodBlock, ImageName::Image_WoodBlock_1,   Rect(740, 450, 83, 40));
	BoxSprite * PillarWoodBlocksBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodBlock, 2.0f, Vect(255,255,0,255), PillarWoodBlocksSprite );
	GameObjectBlock * pPillarWoodBlocks = new GameObjectBlock(GameObjectName::GameObject_Block, PillarWoodBlocksSprite, PillarWoodBlocksBox, BlockType::Wood);
	GenerateBlockPhysicsBody(pPillarWoodBlocks ,3.14f/2.0f);

	GameSprite * PillarWoodBlocksSprite2 = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodBlock,	 ImageName::Image_WoodBlock_1,   Rect(846, 450, 83, 40));
	BoxSprite * PillarWoodBlocksBox2 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodBlock, 2.0f, Vect(255,255,0,255), PillarWoodBlocksSprite2 );
	GameObjectBlock * pPillarWoodBlocks2 = new GameObjectBlock(GameObjectName::GameObject_Block, PillarWoodBlocksSprite2, PillarWoodBlocksBox2, BlockType::Wood);
	GenerateBlockPhysicsBody(pPillarWoodBlocks2 ,3.14f/2.0f);

	GameSprite	*lefthighplank =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(792, 505, 169, 22));
	BoxSprite	*lefthighplankBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), lefthighplank) ;
	GameObjectBlock	*plefthighplank = new GameObjectBlock(GameObjectName::GameObject_Block, lefthighplank, lefthighplankBox , BlockType::Wood);
	GenerateBlockPhysicsBody(plefthighplank);

	GameSprite * GlassBlockLeft = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_GlassBlock,	 ImageName::Image_GlassBlock_1,   Rect(792, 535, 84, 40));
	BoxSprite * GlassBlockLeftBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_GlassBlock, 2.0f, Vect(255,255,0,255), GlassBlockLeft );
	GameObjectBlock * pGlassBlockLeft = new GameObjectBlock(GameObjectName::GameObject_Block, GlassBlockLeft,GlassBlockLeftBox, BlockType::Glass);
	GenerateBlockPhysicsBody(pGlassBlockLeft);

	GameSprite * GlassPointLeft = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_GlassPlank , ImageName::Image_GlassPlank_1,   Rect(792, 595, 83, 22) );
	BoxSprite * GlassPointLeftBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_GlassPlank, 2.0f, Vect(255,255,0,255), GlassPointLeft );
	GameObjectBlock * pGlassPointLeft = new GameObjectBlock(GameObjectName::GameObject_Block, GlassPointLeft,GlassPointLeftBox, BlockType::Glass);
	GenerateBlockPhysicsBody(pGlassPointLeft,3.14f/2.0f);

	GameSprite	*pPigSpriteL = new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_Pig1,	ImageName::Image_Pig, Rect(792, 435, 50, 50) );
	CircleSprite	*PigCircleL = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Pig1, 2.0f, Vect(255,255,0,255),  Rect(792, 435, 50, 50)) ;
	GameObjectPig	*pPigL = new GameObjectPig(GameObjectName::GameObject_Pig, pPigSpriteL, PigCircleL );
	GeneratePigPhysicsBody(pPigL);

	////////////////////////Right

	GameSprite * StonePillar2 = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_StoneBlock,	 ImageName::Image_StoneBlock_1,   Rect(1088, 344, 84, 40));
	BoxSprite * StonePillarBox2 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_StoneBlock, 2.0f, Vect(255,255,0,255), StonePillar2 );
	GameObjectBlock * StonePillarRight = new GameObjectBlock(GameObjectName::GameObject_Block, StonePillar2,StonePillarBox2, BlockType::Stone);
	GenerateBlockPhysicsBody(StonePillarRight,3.14f/2.0f);

	GameSprite	*WoodPillarRight1 =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(1034, 344, 83, 22));
	BoxSprite	*WoodPillarRightBox1 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), WoodPillarRight1) ;
	GameObjectBlock	*pWoodPillarRight1 = new GameObjectBlock(GameObjectName::GameObject_Block, WoodPillarRight1, WoodPillarRightBox1 , BlockType::Wood);
	GenerateBlockPhysicsBody(pWoodPillarRight1,3.14f/2.0f);
	
	GameSprite	*WoodPillarRight2 =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(1140, 344, 83, 22));
	BoxSprite	*WoodPillarRightBox2 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), WoodPillarRight2) ;
	GameObjectBlock	*pWoodPillarRight2 = new GameObjectBlock(GameObjectName::GameObject_Block, WoodPillarRight2, WoodPillarRightBox2 , BlockType::Wood);
	GenerateBlockPhysicsBody(pWoodPillarRight2,3.14f/2.0f);

	GameSprite	*RightlowPlank =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(1088, 397, 169, 22));
	BoxSprite	*RightlowPlankbox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), RightlowPlank) ;
	GameObjectBlock	*pRightlowPlank = new GameObjectBlock(GameObjectName::GameObject_Block, RightlowPlank, RightlowPlankbox , BlockType::Wood);
	GenerateBlockPhysicsBody(pRightlowPlank);
	
	GameSprite	*WoodPillarleft1up =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(1034, 450, 83, 22));
	BoxSprite	*WoodPillarleft1upbox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), WoodPillarleft1up) ;
	GameObjectBlock	*pWoodPillarleft1up = new GameObjectBlock(GameObjectName::GameObject_Block, WoodPillarleft1up, WoodPillarleft1upbox , BlockType::Wood);
	GenerateBlockPhysicsBody(pWoodPillarleft1up,3.14f/2.0f);
	
	GameSprite	*WoodPillarleft2up =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(1014, 450, 83, 22));
	BoxSprite	*WoodPillarleft2upbox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), WoodPillarleft2up);
	GameObjectBlock	*pWoodPillarleft2up = new GameObjectBlock(GameObjectName::GameObject_Block, WoodPillarleft2up, WoodPillarleft2upbox , BlockType::Wood);
	GenerateBlockPhysicsBody(pWoodPillarleft2up,3.14f/2.0f);

	GameSprite	*WoodPillarright1up =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(1140, 450, 83, 22));
	BoxSprite	*WoodPillarright1upbox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), WoodPillarright1up) ;
	GameObjectBlock	*pWoodPillarright1up = new GameObjectBlock(GameObjectName::GameObject_Block, WoodPillarright1up, WoodPillarright1upbox , BlockType::Wood);
	GenerateBlockPhysicsBody(pWoodPillarright1up,3.14f/2.0f);
	
	GameSprite	*WoodPillarright2up =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(1160, 450, 83, 22));
	BoxSprite	*WoodPillarright2upbox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), WoodPillarright2up);
	GameObjectBlock	*pWoodPillarright2up = new GameObjectBlock(GameObjectName::GameObject_Block, WoodPillarright2up, WoodPillarright2upbox , BlockType::Wood);
	GenerateBlockPhysicsBody(pWoodPillarright2up,3.14f/2.0f);

	GameSprite	*RighthighPlank =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(1088, 505, 169, 22));
	BoxSprite	*RighthighPlankbox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), RighthighPlank) ;
	GameObjectBlock	*pRighthighPlank = new GameObjectBlock(GameObjectName::GameObject_Block, RighthighPlank, RighthighPlankbox , BlockType::Wood);
	GenerateBlockPhysicsBody(pRighthighPlank);

	GameSprite * GlassBlockRight = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_GlassBlock,	 ImageName::Image_GlassBlock_1,   Rect(1088, 535, 84, 40));
	BoxSprite * GlassBlockRightBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_GlassBlock, 2.0f, Vect(255,255,0,255), GlassBlockRight );
	GameObjectBlock * pGlassBlockRight = new GameObjectBlock(GameObjectName::GameObject_Block, GlassBlockRight,GlassBlockRightBox, BlockType::Glass);
	GenerateBlockPhysicsBody(pGlassBlockRight);
	
	GameSprite * GlassPointRight = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_GlassPlank , ImageName::Image_GlassPlank_1,   Rect(1088, 595, 83, 22) );
	BoxSprite * GlassPointRightBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_GlassPlank, 2.0f, Vect(255,255,0,255), GlassPointRight );
	GameObjectBlock * pGlassPointRight = new GameObjectBlock(GameObjectName::GameObject_Block, GlassPointRight,GlassPointRightBox, BlockType::Glass);
	GenerateBlockPhysicsBody(pGlassPointRight,3.14f/2.0f);

	GameSprite	*pPigSpriteR = new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_Pig1,	ImageName::Image_Pig, Rect(1088, 435, 50, 50) );
	CircleSprite	*PigCircleR = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Pig1, 2.0f, Vect(255,255,0,255),  Rect(1088, 435, 50, 50)) ;
	GameObjectPig	*pPigR = new GameObjectPig(GameObjectName::GameObject_Pig, pPigSpriteR, PigCircleR );
	GeneratePigPhysicsBody(pPigR);

	}

	if (LEVEL == 2)
	{
	Vect2D X[3];
	X[0] = Vect2D( -(50.0 / 2) , -(50.0 / 2) ); 
	X[1] = Vect2D( (50.0 / 2),  -(50.0 / 2) ); 
	X[2] = Vect2D( -(50.0 / 2), (50.0 / 2) ); 

	GameSprite *pTriSprite = new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_woodBlock,	ImageName::Image_WoodTriangle1, Rect(900, 458, 50, 50) );
	PolySprite *pPolySprite = new PolySprite(SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Block, 2.0f, Vect(255, 255, 0, 255), Vect2D(750, 535), 3, &X[0], PolySprite::LineType::Loop);
	GameObjectBlockTriangle	*pTri = new GameObjectBlockTriangle( GameObjectName::GameObject_Block, pTriSprite, pPolySprite, BlockType::Wood);
	this->GenerateBlockPhysicsBodyTriangle(pTri);

	GameSprite *pTriSprite1 = new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_woodBlock,	ImageName::Image_WoodTriangle1, Rect(900, 458, 50, 50) );
	PolySprite *pPolySprite1 = new PolySprite(SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Block, 2.0f, Vect(255, 255, 0, 255), Vect2D(800, 535), 3, &X[0], PolySprite::LineType::Loop);
	GameObjectBlockTriangle	*pTri1 = new GameObjectBlockTriangle( GameObjectName::GameObject_Block, pTriSprite1, pPolySprite1, BlockType::Wood);
	this->GenerateBlockPhysicsBodyTriangle(pTri1);

	GameSprite *pTriSprite2 = new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_woodBlock,	ImageName::Image_WoodTriangle1, Rect(1050, 535, 50, 50) );
	PolySprite *pPolySprite2 = new PolySprite(SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Block, 2.0f, Vect(255, 255, 0, 255), Vect2D(1040, 535), 3, &X[0], PolySprite::LineType::Loop);
	GameObjectBlockTriangle	*pTri2 = new GameObjectBlockTriangle( GameObjectName::GameObject_Block, pTriSprite2, pPolySprite2, BlockType::Wood);
	this->GenerateBlockPhysicsBodyTriangle(pTri2);

	GameSprite *pTriSprite3 = new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_woodBlock,	ImageName::Image_WoodTriangle1, Rect(1150, 595, 50, 50) );
	PolySprite *pPolySprite3 = new PolySprite(SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Block, 2.0f, Vect(255, 255, 0, 255), Vect2D(1100, 535), 3, &X[0], PolySprite::LineType::Loop);
	GameObjectBlockTriangle	*pTri3 = new GameObjectBlockTriangle( GameObjectName::GameObject_Block, pTriSprite3, pPolySprite3, BlockType::Wood);

	this->GenerateBlockPhysicsBodyTriangle(pTri3);

	GameSprite * BaseBlocksSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_StoneBlock,	 ImageName::Image_StoneBlock_1,   Rect(750, 203, 84, 40));
	BoxSprite * BaseBlockLeftBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_StoneBlock, 2.0f, Vect(255,255,0,255), BaseBlocksSprite );
	GameObjectBlock * BaseBlockLeft = new GameObjectBlock(GameObjectName::GameObject_Block, BaseBlocksSprite,BaseBlockLeftBox, BlockType::Stone);
	GenerateBlockPhysicsBody(BaseBlockLeft);

	GameSprite * BaseBlocksSprite2 = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_StoneBlock,	 ImageName::Image_StoneBlock_1,   Rect(834, 203, 84, 40));
	BoxSprite * BaseBlockLeftBox2 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_StoneBlock, 2.0f, Vect(255,255,0,255), BaseBlocksSprite2 );
	GameObjectBlock * BaseBlockLeft2 = new GameObjectBlock(GameObjectName::GameObject_Block, BaseBlocksSprite2,BaseBlockLeftBox2, BlockType::Stone);
	GenerateBlockPhysicsBody(BaseBlockLeft2);


	GameSprite * WoodCubeSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodCube,	ImageName::Image_WoodCube_1,   Rect(750, 284, 40, 40));
	BoxSprite * WoodCubRightBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodCube, 2.0f, Vect(255,255,0,255), WoodCubeSprite );
	GameObjectBlock * WoodCubeRight = new GameObjectBlock(GameObjectName::GameObject_Block, WoodCubeSprite,WoodCubRightBox, BlockType::Wood);
	GenerateBlockPhysicsBody(WoodCubeRight);

	GameSprite * WoodBlockSprite2 = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodCube,	ImageName::Image_WoodBlock_1,   Rect(812, 284, 84, 40));
	BoxSprite * WoodBlockRightBox2 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodCube, 2.0f, Vect(255,255,0,255), WoodBlockSprite2 );
	GameObjectBlock * WoodBlockRight2 = new GameObjectBlock(GameObjectName::GameObject_Block, WoodBlockSprite2,WoodBlockRightBox2, BlockType::Wood);
	GenerateBlockPhysicsBody(WoodBlockRight2);

	GameSprite * WoodBlockSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodCube,	ImageName::Image_WoodBlock_1,   Rect(770, 245, 84, 40));
	BoxSprite * WoodBlockRightBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodCube, 2.0f, Vect(255,255,0,255), WoodBlockSprite );
	GameObjectBlock * WoodBlockRight = new GameObjectBlock(GameObjectName::GameObject_Block, WoodBlockSprite,WoodBlockRightBox, BlockType::Wood);
	GenerateBlockPhysicsBody(WoodBlockRight);

	GameSprite * WoodCubeSprite2 = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodCube,	ImageName::Image_WoodCube_1,   Rect(832, 245, 40, 40));
	BoxSprite * WoodCubRightBox2 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodCube, 2.0f, Vect(255,255,0,255), WoodCubeSprite2 );
	GameObjectBlock * WoodCubeRight2 = new GameObjectBlock(GameObjectName::GameObject_Block, WoodCubeSprite2,WoodCubRightBox2, BlockType::Wood);
	GenerateBlockPhysicsBody(WoodCubeRight2);

	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	GameSprite	*MidPlank =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(937, 235, 169, 22));
	BoxSprite	*MidplankBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), MidPlank) ;
	GameObjectBlock	*pMidPlank = new GameObjectBlock(GameObjectName::GameObject_Block, MidPlank, MidplankBox , BlockType::Wood);
	GenerateBlockPhysicsBody(pMidPlank);

	GameSprite	*pPigSpriteM = new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_Pig1,	ImageName::Image_Pig, Rect(937, 280, 70, 70) );
	CircleSprite	*PigCircleM = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Pig1, 2.0f, Vect(255,255,0,255),  Rect(937, 280, 70, 70)) ;
	GameObjectPig	*pPigM = new GameObjectPig(GameObjectName::GameObject_Pig, pPigSpriteM, PigCircleM );
	GeneratePigPhysicsBody(pPigM);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	GameSprite * BaseBlocksSprite3 = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_StoneBlock,	 ImageName::Image_StoneBlock_1,   Rect(1034, 203, 84, 40));
	BoxSprite * BaseBlockRightBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_StoneBlock, 2.0f, Vect(255,255,0,255), BaseBlocksSprite3 );
	GameObjectBlock * BaseBlockRight = new GameObjectBlock(GameObjectName::GameObject_Block, BaseBlocksSprite3,BaseBlockRightBox, BlockType::Stone);
	GenerateBlockPhysicsBody(BaseBlockRight);

	GameSprite * BaseBlocksSprite4 = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_StoneBlock,	 ImageName::Image_StoneBlock_1,   Rect(1116, 203, 84, 40));
	BoxSprite * BaseBlockRightBox2 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_StoneBlock, 2.0f, Vect(255,255,0,255), BaseBlocksSprite4 );
	GameObjectBlock * BaseBlockRight2 = new GameObjectBlock(GameObjectName::GameObject_Block, BaseBlocksSprite4,BaseBlockRightBox2, BlockType::Stone);
	GenerateBlockPhysicsBody(BaseBlockRight2);

	GameSprite * WoodCubeSpriteR = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodCube,	ImageName::Image_WoodCube_1,   Rect(1044, 284, 40, 40));
	BoxSprite * WoodCubRightBoxR = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodCube, 2.0f, Vect(255,255,0,255), WoodCubeSpriteR );
	GameObjectBlock * WoodCubeRightR = new GameObjectBlock(GameObjectName::GameObject_Block, WoodCubeSpriteR,WoodCubRightBoxR, BlockType::Wood);
	GenerateBlockPhysicsBody(WoodCubeRightR);

	GameSprite * WoodBlockSprite2R = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodCube,	ImageName::Image_WoodBlock_1,   Rect(1108, 284, 84, 40));
	BoxSprite * WoodBlockRightBox2R = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodCube, 2.0f, Vect(255,255,0,255), WoodBlockSprite2R );
	GameObjectBlock * WoodBlockRight2R = new GameObjectBlock(GameObjectName::GameObject_Block, WoodBlockSprite2R,WoodBlockRightBox2R, BlockType::Wood);
	GenerateBlockPhysicsBody(WoodBlockRight2R);

	GameSprite * WoodBlockSpriteR = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodCube,	ImageName::Image_WoodBlock_1,   Rect(1064, 245, 84, 40));
	BoxSprite * WoodBlockRightBoxR = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodCube, 2.0f, Vect(255,255,0,255), WoodBlockSpriteR );
	GameObjectBlock * WoodBlockRightR = new GameObjectBlock(GameObjectName::GameObject_Block, WoodBlockSpriteR,WoodBlockRightBoxR, BlockType::Wood);
	GenerateBlockPhysicsBody(WoodBlockRightR);

	GameSprite * WoodCubeSprite2R = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodCube,	ImageName::Image_WoodCube_1,   Rect(1126, 245, 40, 40));
	BoxSprite * WoodCubRightBox2R = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodCube, 2.0f, Vect(255,255,0,255), WoodCubeSprite2R);
	GameObjectBlock * WoodCubeRight2R = new GameObjectBlock(GameObjectName::GameObject_Block, WoodCubeSprite2R,WoodCubRightBox2R, BlockType::Wood);
	GenerateBlockPhysicsBody(WoodCubeRight2R);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
	GameSprite * StonePillar = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_StoneBlock,	 ImageName::Image_StoneBlock_1,   Rect(792, 344, 84, 40));
	BoxSprite * StonePillarBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_StoneBlock, 2.0f, Vect(255,255,0,255), StonePillar );
	GameObjectBlock * StonePillarLeft = new GameObjectBlock(GameObjectName::GameObject_Block, StonePillar,StonePillarBox, BlockType::Stone);
	GenerateBlockPhysicsBody(StonePillarLeft,3.14f/2.0f);

	GameSprite	*WoodPillarleft1 =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(740, 344, 83, 22));
	BoxSprite	*WoodPillarleft1box = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), WoodPillarleft1) ;
	GameObjectBlock	*pWoodPillarleft1 = new GameObjectBlock(GameObjectName::GameObject_Block, WoodPillarleft1, WoodPillarleft1box , BlockType::Wood);
	GenerateBlockPhysicsBody(pWoodPillarleft1,3.14f/2.0f);
	
	GameSprite	*WoodPillarleft2 =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(846, 344, 83, 22));
	BoxSprite	*WoodPillarleft2box = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), WoodPillarleft2) ;
	GameObjectBlock	*pWoodPillarleft2 = new GameObjectBlock(GameObjectName::GameObject_Block, WoodPillarleft2, WoodPillarleft2box , BlockType::Wood);
	GenerateBlockPhysicsBody(pWoodPillarleft2,3.14f/2.0f);

	GameSprite	*leftlowplank =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(792, 397, 169, 22));
	BoxSprite	*leftlowplankBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), leftlowplank) ;
	GameObjectBlock	*pleftlowplank = new GameObjectBlock(GameObjectName::GameObject_Block, leftlowplank, leftlowplankBox , BlockType::Wood);
	GenerateBlockPhysicsBody(pleftlowplank);

	GameSprite * PillarWoodBlocksSprite = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodBlock, ImageName::Image_WoodBlock_1,   Rect(740, 450, 83, 40));
	BoxSprite * PillarWoodBlocksBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodBlock, 2.0f, Vect(255,255,0,255), PillarWoodBlocksSprite );
	GameObjectBlock * pPillarWoodBlocks = new GameObjectBlock(GameObjectName::GameObject_Block, PillarWoodBlocksSprite, PillarWoodBlocksBox, BlockType::Wood);
	GenerateBlockPhysicsBody(pPillarWoodBlocks ,3.14f/2.0f);

	GameSprite * PillarWoodBlocksSprite2 = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodBlock,	 ImageName::Image_WoodBlock_1,   Rect(846, 450, 83, 40));
	BoxSprite * PillarWoodBlocksBox2 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodBlock, 2.0f, Vect(255,255,0,255), PillarWoodBlocksSprite2 );
	GameObjectBlock * pPillarWoodBlocks2 = new GameObjectBlock(GameObjectName::GameObject_Block, PillarWoodBlocksSprite2, PillarWoodBlocksBox2, BlockType::Wood);
	GenerateBlockPhysicsBody(pPillarWoodBlocks2 ,3.14f/2.0f);

	GameSprite	*lefthighplank =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(792, 505, 169, 22));
	BoxSprite	*lefthighplankBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), lefthighplank) ;
	GameObjectBlock	*plefthighplank = new GameObjectBlock(GameObjectName::GameObject_Block, lefthighplank, lefthighplankBox , BlockType::Wood);
	GenerateBlockPhysicsBody(plefthighplank);

	GameSprite	*pPigSpriteL = new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_Pig1,	ImageName::Image_HelmetPig, Rect(792, 435, 50, 50));
	CircleSprite	*PigCircleL = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Pig1, 2.0f, Vect(255,255,0,255),  Rect(792, 435, 50, 50)) ;
	GameObjectPig	*pPigL = new GameObjectPig(GameObjectName::GameObject_Pig, pPigSpriteL, PigCircleL, true);
	GeneratePigPhysicsBody(pPigL);

	////////////////////////Right

	GameSprite * StonePillar2 = new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_StoneBlock,	 ImageName::Image_StoneBlock_1,   Rect(1088, 344, 84, 40));
	BoxSprite * StonePillarBox2 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_StoneBlock, 2.0f, Vect(255,255,0,255), StonePillar2 );
	GameObjectBlock * StonePillarRight = new GameObjectBlock(GameObjectName::GameObject_Block, StonePillar2,StonePillarBox2, BlockType::Stone);
	GenerateBlockPhysicsBody(StonePillarRight,3.14f/2.0f);

	GameSprite	*WoodPillarRight1 =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(1034, 344, 83, 22));
	BoxSprite	*WoodPillarRightBox1 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), WoodPillarRight1) ;
	GameObjectBlock	*pWoodPillarRight1 = new GameObjectBlock(GameObjectName::GameObject_Block, WoodPillarRight1, WoodPillarRightBox1 , BlockType::Wood);
	GenerateBlockPhysicsBody(pWoodPillarRight1,3.14f/2.0f);
	
	GameSprite	*WoodPillarRight2 =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(1140, 344, 83, 22));
	BoxSprite	*WoodPillarRightBox2 = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), WoodPillarRight2) ;
	GameObjectBlock	*pWoodPillarRight2 = new GameObjectBlock(GameObjectName::GameObject_Block, WoodPillarRight2, WoodPillarRightBox2 , BlockType::Wood);
	GenerateBlockPhysicsBody(pWoodPillarRight2,3.14f/2.0f);

	GameSprite	*RightlowPlank =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(1088, 397, 169, 22));
	BoxSprite	*RightlowPlankbox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), RightlowPlank) ;
	GameObjectBlock	*pRightlowPlank = new GameObjectBlock(GameObjectName::GameObject_Block, RightlowPlank, RightlowPlankbox , BlockType::Wood);
	GenerateBlockPhysicsBody(pRightlowPlank);
	
	GameSprite	*WoodPillarleft1up =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(1034, 450, 83, 22));
	BoxSprite	*WoodPillarleft1upbox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), WoodPillarleft1up) ;
	GameObjectBlock	*pWoodPillarleft1up = new GameObjectBlock(GameObjectName::GameObject_Block, WoodPillarleft1up, WoodPillarleft1upbox , BlockType::Wood);
	GenerateBlockPhysicsBody(pWoodPillarleft1up,3.14f/2.0f);
	
	GameSprite	*WoodPillarleft2up =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(1014, 450, 83, 22));
	BoxSprite	*WoodPillarleft2upbox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), WoodPillarleft2up);
	GameObjectBlock	*pWoodPillarleft2up = new GameObjectBlock(GameObjectName::GameObject_Block, WoodPillarleft2up, WoodPillarleft2upbox , BlockType::Wood);
	GenerateBlockPhysicsBody(pWoodPillarleft2up,3.14f/2.0f);

	GameSprite	*WoodPillarright1up =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(1140, 450, 83, 22));
	BoxSprite	*WoodPillarright1upbox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), WoodPillarright1up) ;
	GameObjectBlock	*pWoodPillarright1up = new GameObjectBlock(GameObjectName::GameObject_Block, WoodPillarright1up, WoodPillarright1upbox , BlockType::Wood);
	GenerateBlockPhysicsBody(pWoodPillarright1up,3.14f/2.0f);
	
	GameSprite	*WoodPillarright2up =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(1160, 450, 83, 22));
	BoxSprite	*WoodPillarright2upbox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), WoodPillarright2up);
	GameObjectBlock	*pWoodPillarright2up = new GameObjectBlock(GameObjectName::GameObject_Block, WoodPillarright2up, WoodPillarright2upbox , BlockType::Wood);
	GenerateBlockPhysicsBody(pWoodPillarright2up,3.14f/2.0f);

	GameSprite	*RighthighPlank =new GameSprite (SpriteBatchName::SpriteBatch_Blocks, SpriteName::Sprite_woodPlankShort1, ImageName::Image_woodPlankShort_1, Rect(1088, 505, 169, 22));
	BoxSprite	*RighthighPlankbox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_woodPlankShort1, 2.0f, Vect(255,255,0,255), RighthighPlank) ;
	GameObjectBlock	*pRighthighPlank = new GameObjectBlock(GameObjectName::GameObject_Block, RighthighPlank, RighthighPlankbox , BlockType::Wood);
	GenerateBlockPhysicsBody(pRighthighPlank);

	GameSprite	*pPigSpriteR = new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_Pig1,	ImageName::Image_HelmetPig, Rect(1088, 435, 50, 50));
	CircleSprite	*PigCircleR = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Pig1, 2.0f, Vect(255,255,0,255),  Rect(1088, 435, 50, 50)) ;
	GameObjectPig	*pPigR = new GameObjectPig(GameObjectName::GameObject_Pig, pPigSpriteR, PigCircleR, true );
	GeneratePigPhysicsBody(pPigR);

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////Setting up the Background//////////////////////////////////////////////////////////////////////////
	 
	float w = 1280;
	float h = 864;
	float x = w  / 2;
	float y =  h / 2;

	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundGrass, ImageName::Image_BackgroundGrass, Rect(-x, y, w, h) );
	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundGround, ImageName::Image_BackgroundGround, Rect(-x, y, w, h) );
	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundCloud, ImageName::Image_BackgroundCloud, Rect(-x, y, w, h) );
	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundTrees, ImageName::Image_BackgroundTrees, Rect(-x, y, w, h));
	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundTrees, ImageName::Image_BackgroundTrees, Rect(-x, y, w, h) );

	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundGrass, ImageName::Image_BackgroundGrass, Rect(x, y, w, h) );
	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundGround, ImageName::Image_BackgroundGround, Rect(x, y, w, h) );
	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundCloud, ImageName::Image_BackgroundCloud, Rect(x, y, w, h) );
	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundTrees, ImageName::Image_BackgroundTrees, Rect(x, y, w, h));
	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundTrees, ImageName::Image_BackgroundTrees, Rect(x, y, w, h) );

	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundGrass, ImageName::Image_BackgroundGrass, Rect(x * 2, y, w, h) );
	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundGround, ImageName::Image_BackgroundGround, Rect(x * 2, y, w, h) );
	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundCloud, ImageName::Image_BackgroundCloud, Rect(x * 2, y, w , h) );
	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundTrees, ImageName::Image_BackgroundTrees, Rect(x * 2, y, w , h));
	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundTrees, ImageName::Image_BackgroundTrees, Rect(x * 2, y, w , h) );

	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundGrass, ImageName::Image_BackgroundGrass, Rect(x * 4, y, w, h) );
	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundGround, ImageName::Image_BackgroundGround, Rect(x * 4, y, w, h) );
	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundCloud, ImageName::Image_BackgroundCloud, Rect(x * 4, y, w , h) );
	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundTrees, ImageName::Image_BackgroundTrees, Rect(x * 4, y, w , h));
	new GameSprite( SpriteBatchName::SpriteBatch_Background,SpriteName::Sprite_BackgroundTrees, ImageName::Image_BackgroundTrees, Rect(x * 4, y, w , h) );

}

void World::CreateBlueBird(float x, float y, GameObjectBird* pObject, b2Vec2 Impulse)
{
		//////Create Blue Bird//////
	GameSprite *pBirdSprite1 = 	new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_Blue, ImageName::Image_BlueBird, Rect(x, y, 25, 25) );
	CircleSprite *pBirdCircle1 = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f,  Color(Yellow), Rect(x, y, 25, 25)) ;
	GameObjectBird *pBird1 = new GameObjectBird(GameObjectName::GameObject_Bird, pBirdSprite1, pBirdCircle1, BirdType::BLUE_BIRD);
	GenerateBirdPhysicsBody(pBird1);

	pBird1->pBody->SetLinearVelocity(pObject->pBody->GetLinearVelocity());
	pBird1->pBody->ApplyLinearImpulse(Impulse, pBird1->pBody->GetPosition() , true);

	pBird1->pBody->SetActive(true);
	pBird1->active = true;
	pBird1->launched = true;
	pBird1->powerused = true;
	BirdsinWorld ++;
}

void World::CreateEgg(float x, float y, b2Vec2 Impulse)
{
		///Create Egg////
	GameSprite *pEggSprite = 	new GameSprite (SpriteBatchName::SpriteBatch_Birds,  SpriteName::Sprite_Egg, ImageName::Image_WhiteEgg, Rect(x, y, 30, 30) );
	CircleSprite *pEggCircle = new CircleSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Box_Bird, 2.0f,  Color(Yellow), Rect(x, y, 30, 30)) ;
	GameObjectEgg *pEgg = new GameObjectEgg(GameObjectName::GameObject_Egg, pEggSprite, pEggCircle );
	GenerateEggPhysicsBody(pEgg); //Create Egg Physics Object
	pEgg->pBody->ApplyLinearImpulse( Impulse, pEgg->pBody->GetPosition(), true);
	pEgg->pBody->SetActive(true);

}

void World::CreateSmokeCloud (float x, float y)
{
	this->TrailList->DisplayNodes(x, y, true);
}
void World::CreateNewGameObject(  float x, float y, GameObjectBird* pObject, b2Vec2 Impulse, GameObjectName::Name ObjectName)
{

	switch(ObjectName)
	{
		case GameObjectName::GameObject_Bird:
			CreateBlueBird(x, y, pObject, Impulse );
		break;

		case GameObjectName::GameObject_Egg:
			CreateEgg(x, y, b2Vec2(0.0f, -5.0f) );
		break;
	}
	///////////////////////////
}


void World::loadWorldPhysics()
{
	///Create Gravity and Create World
	b2Vec2 gravity(0.0, -10.0f);
	pWorld =  new b2World(gravity);

	AngryContactListener *myContactListener = new AngryContactListener();
	pWorld->SetContactListener( myContactListener );

	GameSprite * GroundGameSprite = new GameSprite (SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Ground, ImageName::Image_Ground, Rect(360, 170, 3280, 25) );
	BoxSprite * GroundBox = new BoxSprite( SpriteBatchName::SpriteBatch_Debug, SpriteName::Sprite_Ground, 2.0f, Vect(255,255,0,255), Rect(360, 170, 3280, 25) );
	GameObjectGround * GroundObj = new GameObjectGround(GameObjectName::GameObject_Ground,GroundGameSprite, GroundBox);
	GroundObj;

	b2BodyDef StaticBodyDef;
	StaticBodyDef.type = b2_staticBody;

	StaticBodyDef.position.Set( PixelToMeter(GroundObj->pBoxSprite->posX),PixelToMeter(GroundObj->pBoxSprite->posY));
	StaticBodyDef.angle = 	3.14f ;
	b2Body *pStaticBody = this->pWorld->CreateBody(&StaticBodyDef);
		
	b2PolygonShape GroundShape;

	GroundShape.SetAsBox( PixelToMeter(GroundObj->pBoxSprite->origWidth * 0.5f), PixelToMeter(GroundObj->pBoxSprite->origHeight * 0.5f) );
	pStaticBody->CreateFixture( &GroundShape, 0.0f);
	pStaticBody->GetFixtureList()->SetUserData(GroundObj);
	pStaticBody->SetActive(false);

	pStaticBody->SetUserData( GroundObj);	
	GroundObj->pBody = pStaticBody;

}
void World::KillGameObject(GameObject * pGameObj)
{
	pGameObj->pBody->SetActive(false);
	pGameObj->pBody->DestroyFixture(pGameObj->pBody->GetFixtureList());
	pGameObj->pGameSprite->display = false;

	if (pGameObj->gameObjName == GameObjectName::GameObject_Block)
		((GameObjectBlock *)pGameObj)->pBoxSprite->disable();
				
	if (pGameObj->gameObjName == GameObjectName::GameObject_Pig)
		((GameObjectPig *)pGameObj)->pCircleSprite->disable();

	if (pGameObj->gameObjName == GameObjectName::GameObject_Egg)
		((GameObjectEgg *)pGameObj)->pCircleSprite->disable();

	if (pGameObj->gameObjName == GameObjectName::GameObject_Bird)
	{
		((GameObjectBird *)pGameObj)->pCircleSprite->disable();
		((GameObjectBird *)pGameObj)->launched = false;
		this->removebird = true;
		this->BirdsinWorld--;
	}

	pGameObj->isAlive = false;
}
void World::CatchInput(GameObject * pGameObj, GLFWwindow* window)
{
	MouseTest(window, (GameObjectBird *)pGameObj, this);

	KeyboardTest(window, pGameObj);
}

static bool Test = false;
void resetCameratoslingshot()
{			
		Camera *pCam = Camera::Instance();

		Vect pos;
		Vect lookAt;
		pCam->TargetWorldScreen( pos, lookAt, WINDOWWIDTH/2, WINDOWHEIGHT/2);

		Vect up;
		pCam->getUp( up );
		pCam->setOrientAndPosition( up, lookAt, pos );
		userinput = false;
}
void followBird ( GameObjectBird * pBird)
{
	if (!userinput)
	{
		if (POWERPOINT.Length() == 0)
		{
			if (pBird->launched)
			{
				Camera *pCam = Camera::Instance();
				Vect POS;
				pCam->getPos(POS);
				bool endpos = (POS[x] + WINDOWWIDTH >= LEVELWIDTH ) && (POS[x] < 0); 

				if (pBird->pos.x > WINDOWWIDTH/2 && !endpos )
				{
					b2Vec2 birdPos = pBird->pos;

					Vect pos;
					Vect lookAt;
					pCam->TargetWorldScreen( pos, lookAt, birdPos.x, WINDOWHEIGHT/2 );

					Vect up;
					pCam->getUp( up );
					pCam->setOrientAndPosition( up, lookAt, pos );
				}
			}
		}
		else
		{
			Camera *pCam = Camera::Instance();
			Vect POS;
			pCam->getPos(POS);

			bool endpos = (POS[x] + WINDOWWIDTH >= LEVELWIDTH ) && (POS[x] < 0); 

			if ( POWERPOINT.x > WINDOWWIDTH/2 && !endpos )
			{
				b2Vec2 birdPos = POWERPOINT;

				Vect pos;
				Vect lookAt;
				pCam->TargetWorldScreen( pos, lookAt, birdPos.x, WINDOWHEIGHT/2 );

				Vect up;
				pCam->getUp( up );
				pCam->setOrientAndPosition( up, lookAt, pos );
			}
		}
	}
}



void World::ActivateScene(float32 dt)
{
	if (starttimer >= STARTTIME)
	{
		if ( this->isfirstStep)
		{
			b2Body *pBodies = this->pWorld->GetBodyList();
	
			while( pBodies != 0 )
			{
				GameObject *pGObj = (GameObject *)pBodies->GetUserData();


				if (pGObj->gameObjName != GameObjectName::GameObject_Bird)
					pBodies->SetActive(true);

				pBodies = pBodies->GetNext();
			}

			isfirstStep = false;
		}
	}
	else
	{
		starttimer += dt;

	}

}

bool World::OutofBounds(GameObject *pGameObj)
{
	if ( (pGameObj->pGameSprite->posX - pGameObj->pGameSprite->origWidth/2) > LEVELWIDTH
		|| (pGameObj->pGameSprite->posY + pGameObj->pGameSprite->origHeight/2) < 150 
		|| (pGameObj->pGameSprite->posX + pGameObj->pGameSprite->origWidth/2) < 0  )
	{
		pGameObj->ApplyDamage(100.0f);
		return true;
	}

	return false;
}
void World::getNextBird(GameObject *pGameObj)
{
	if (pGameObj->gameObjName == GameObjectName::GameObject_Bird)
	{
		if (((GameObjectBird *)(pGameObj))->type == this->Queue[CurrentBird])
		{
			GameObjectBird * pBird = (GameObjectBird *)pGameObj;

			pBird->pGameSprite->posX = 143;
			pBird->pGameSprite->posY = 270;
			pBird->pCircleSprite->posX = 143;
			pBird->pCircleSprite->posY = 270;
			pBird->pBody->SetTransform(b2Vec2(PixelToMeter(143.0f),PixelToMeter(270.0f)), 0.0f);
			pBird->pBody->SetActive(false);
			pBird->launched = false;
			pBird->active = true;
			pBird->pGameSprite->display = true;
			pBird->health = 50;
			pBird->state = NORMAL;
			pBird->update( pGameObj->pBody->GetPosition(), pGameObj->pBody->GetAngle());
			
			NEWBIRD = false;
			CurrentType = Queue[CurrentBird];
			
		}
	}
}
void World::RemoveAbird(GameObject *pGameObj)
{

	if (pGameObj->gameObjName == GameObjectName::GameObject_Bird && this->removebird)
	{
		if (((GameObjectBird *)(pGameObj))->active == false && ((GameObjectBird *)(pGameObj))->health != 0)
		{
			if (this->BirdsinWorld <=0)
			{

				this->CurrentBird++;
				
				this->BirdsinWorld = 0;
				
				EXPLOSIONPOINT.SetZero();
				POWERPOINT.SetZero();
				resetCameratoslingshot();
				NEWBIRD = true;
				this->removebird = false;
			}
			else
			{
				this->removebird = false;				
			}
		}
	}
}

unsigned short lfsr = 0xACE1u;
unsigned bit;

unsigned random()
{
	bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
	return lfsr = (unsigned short) ((lfsr >> 1) | (bit << 15));
}

void applyBlastImpulse(GameObject * pGameObject, float blastPower) {
	b2Vec2 blastDir = pGameObject->pBody->GetPosition() - EXPLOSIONPOINT;
      float distance = blastDir.Normalize();

      if ( distance == 0 )
          return;

	  if (pGameObject->gameObjName == GameObjectName::GameObject_Block || pGameObject->gameObjName == GameObjectName::GameObject_Pig )		 
	  {
		  if (!pGameObject->markedfordeath)
		  {
			float impulseMag = blastPower * (1 / distance)* (1 / distance);
			pGameObject->pBody->ApplyLinearImpulse( impulseMag * blastDir, pGameObject->pBody->GetPosition(), true);
			pGameObject->ApplyDamage((blastPower/distance)/2);	
		  }
	  }
  }

void World::Update( float32 dt, GLFWwindow* window)
{	
	window;

	randomVal = (int)random();

	this->FeatherEmitter->UpdateParticles();
	this->SplinterEmitter->UpdateParticles();

	this->pWorld->Step( dt, this->velocityIterations, this->positionIternations);

	//// Update graphics object
	b2Body *pBody = this->pWorld->GetBodyList();

	while( pBody != 0 )
	{
		GameObject *pGameObj = (GameObject *)pBody->GetUserData();

		if( pGameObj != 0 )
		{
			OutofBounds(pGameObj);
			RemoveAbird(pGameObj);
			if (NEWBIRD)
				this->getNextBird(pGameObj);

			if (EXPLOSIONPOINT.Length() != 0)
				applyBlastImpulse(pGameObj, 5.0f);

			if (pGameObj->health <=0 && pGameObj->isAlive)
			{
				KillGameObject(pGameObj);
			}
			else
			{
				pGameObj->update( pBody->GetPosition(), pBody->GetAngle());
			
				if (pGameObj->gameObjName == GameObjectName::GameObject_Bird)
				{
					followBird((GameObjectBird *)pGameObj);
					CatchInput(pGameObj,window);
				}
			}

			
		}
		
		if (!startworld)
		{
			pBody->SetAngularVelocity(0.0f);
			pBody->SetLinearVelocity(b2Vec2_zero);
		}

		pBody = pBody->GetNext();
	}
	
	
	ActivateScene(dt);
}

b2World * World::getWorldPtr()
{
	return pWorld;
}