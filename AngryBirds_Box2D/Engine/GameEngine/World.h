#pragma once

#include "AzulCore.h"
#include "Box2D.h"
#include "AzulStopWatch.h"
#include "GameObject.h"
#include "Color.h"

#include "GameObjectPlatform.h"
#include "GameObjectBird.h"
#include "GameObjectBlock.h"
#include "GameObjectPig.h"
#include "GameObjectSlingShot.h"
#include "GameObjectGround.h"
#include "GameObjectParticle.h"
#include "GameObjectEgg.h"
#include "GameObjectBlockRound.h"
#include "GameObjectBlockTriangle.h"
#include "Trail.h"


class ParticleEmitter;
enum _entityCategory {
    BOUNDARY =          0x0001,
    BIRD =				0x0002,
    PIG =				0x0004,
    BLOCK =				0x0008,
    PARTICLE =			0x0010
 };
class World
{
public:
	
	~World(void);
	
	void initializeWorld();
	void Update( float32, GLFWwindow* X);
	b2World * getWorldPtr();
	GameObjectGround * getGroundBodyptr(){ return this->pGround; };
	void CreateNewGameObject(float, float, GameObjectBird*, b2Vec2, GameObjectName::Name );
	
	static World & getInstance()
	{
		static World Instance;
		return Instance;
	};

	int BirdsinWorld;

	void CreateSmokeCloud (float x, float y);

	Trail * TrailList;
	
	ParticleEmitter * FeatherEmitter;
	ParticleEmitter * SplinterEmitter;	
	BirdType CurrentType;
private:
	World(void);

	void loadWorldPhysics();
	void loadWorldObjects();
	void loadAssets();

	void GeneratePlatformPhysicsBody(GameObjectPlatform *);
	void GenerateBlockPhysicsBody(GameObjectBlock * inObject, float rotation = 0.0f);
	void GenerateBirdPhysicsBody(GameObjectBird * inObject);
	void GeneratePigPhysicsBody(GameObjectPig * inObject);
	void GenerateSlingShotPhysicsBody(GameObjectSlingshot * inObject);
	void GenerateEggPhysicsBody(GameObjectEgg * inObject);
	void GenerateBlockPhysicsBodyRound(GameObjectBlockRound *);
	void GenerateBlockPhysicsBodyTriangle(GameObjectBlockTriangle *, float rotation = 0);
	void CreateEgg(float x, float y, b2Vec2 Impulse);
	void CreateBlueBird(float x, float y, GameObjectBird* pObject, b2Vec2 Impulse);
	
	void getNextBird(GameObject *);
	void KillGameObject(GameObject * pGameObj);
	void CatchInput(GameObject * pGameObj, GLFWwindow* window);
	void ActivateScene(float32 dt);
	void RemoveAbird(GameObject *pGameObj);

	bool OutofBounds(GameObject *);
	b2World *pWorld;
	GameObjectGround * pGround;
	float32 starttimer;
	
	BirdType * Queue;
	int CurrentBird;
	

	bool isfirstStep;
	bool removebird;
	bool NEWBIRD;

	int velocityIterations;
	int positionIternations;

};

