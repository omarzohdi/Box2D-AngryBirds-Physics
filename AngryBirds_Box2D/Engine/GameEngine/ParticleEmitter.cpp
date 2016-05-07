#include "ParticleEmitter.h"


ParticleEmitter::ParticleEmitter(ParticlesType Type)
{
	this->particlelist = new ParticleList(Type);
	this->SpawnPoints = 0;
}

void ParticleEmitter::UpdateParticles()
{
	ParticlePositions * ptr = this->SpawnPoints;
	ParticlePositions * temp;
	while (ptr != 0)
	{
		temp = ptr;
		
		this->SpawnParticle(ptr->SpawnPosition, ptr->SpawnImpulse, ptr->type);
		
		ptr = ptr->pnext;
		
		temp->pnext = 0;
		delete temp;
	}
	this->SpawnPoints = 0;
	this->particlelist->Update();
}

void ParticleEmitter::SpawnParticle(b2Vec2 SpawnPoint,b2Vec2 SpawnImpulse, int splintertype)
{
	this->particlelist->Add(SpawnPoint, SpawnImpulse, splintertype);
}

void ParticleEmitter::MarkPoistionforAdd(b2Vec2 SpawnPoint, b2Vec2 SpawnImpulse,int splintertype)
{
	ParticlePositions * Temp = new ParticlePositions(SpawnPoint,SpawnImpulse, splintertype);

	Temp->pnext = this->SpawnPoints;
	this->SpawnPoints = Temp;
}

ParticleEmitter::~ParticleEmitter(void)
{
}
