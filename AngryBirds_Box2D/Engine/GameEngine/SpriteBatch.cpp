#include "SpriteBatchManager.h"
#include "SpriteBatch.h"
#include "EnumName.h"


SpriteBatch::SpriteBatch()
{
	this->batchName = SpriteBatchName::Not_Initialized;
}

void SpriteBatch::privDraw(Sprite * sprite)
{
	sprite->Draw();
}

void SpriteBatch::Set(SpriteBatchName::Name _batchName)
{
	this->ManLink::Initialize();

	this->batchName = _batchName;
}

EnumName SpriteBatch::getName()
{
	return SpriteBatchName( (EnumName::Name)this->batchName );
}