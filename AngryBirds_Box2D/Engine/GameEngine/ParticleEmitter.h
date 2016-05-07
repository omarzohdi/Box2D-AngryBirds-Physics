#ifndef PARTEMIT_H
#define PARTEMIT_H

#include "ParticleList.h"


struct ParticlePositions
{
	b2Vec2 SpawnPosition;
	b2Vec2 SpawnImpulse;
	ParticlePositions * pnext;
	int type;

	ParticlePositions(b2Vec2 Pos, b2Vec2 impulse, int Type = 0)
	{
		this->SpawnPosition = Pos;
		this->SpawnImpulse = impulse;
		this->type = Type;
	}
};

class ParticleEmitter
{

public:
	ParticleEmitter(ParticlesType);
	~ParticleEmitter(void);

	
	void MarkPoistionforAdd(b2Vec2,b2Vec2,int splintertype=0);
	void UpdateParticles();
	void SpawnParticle(b2Vec2,b2Vec2, int splintertype=0);

private:
	
	ParticlePositions * SpawnPoints;
	
	
	ParticleEmitter(void){};

	ParticleList * particlelist;

};

#endif