#include "PixelToMeter.h"
#include "GameObject.h"
#include "BoxSprite.h"
#include "Box2D.h"

	
GameObject::GameObject( )
{

	this->pBody = 0;
	this->health = 20;
	this->isAlive = true;
	this->markedfordeath = false;
}

bool GameObject::IsMarked()
{
	return this->markedfordeath;
}

void GameObject::MarkforDeath()
{
	this->markedfordeath = true; 
}

GameObject::~GameObject()
{

}







