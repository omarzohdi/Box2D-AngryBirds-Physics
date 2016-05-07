#ifndef ANGRY_CONTACT_LISTENER_H
#define ANGRY_CONTACT_LISTENER_H

#include "Box2D.h"
#include "PixelToMeter.h"
#include "AzulStopWatch.h"

#include "World.h"



extern AzulStopWatch stopWatch;
extern AzulStopWatch totalWatch;
extern bool startworld;

class AngryContactListener : public b2ContactListener
{

public:

	AngryContactListener();

	void BeginContact(b2Contact* pContact);
	void EndContact(b2Contact* );
	void PreSolve(b2Contact* , const b2Manifold* );
	void PostSolve(b2Contact* , const b2ContactImpulse* );
	
	int checkforstatic(GameObject * gObjA, GameObject * GObjB);

	void CollideDynamics(GameObject * gObjA, GameObject * gObjB, const b2ContactImpulse * pImpulse);
	void CollideStatic(GameObject * gObjA, const b2ContactImpulse * pImpulse);
	float getTypeModifier(BlockType type);

};

#endif