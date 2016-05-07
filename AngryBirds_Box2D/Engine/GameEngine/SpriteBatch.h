#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H

#include "AzulHeader.h"

class SpriteBatch: public ManLink
{
public:
	SpriteBatch();

	void Set(SpriteBatchName::Name batchName);
	EnumName getName();
	
public:

	// data: -----------------------------------------------------------------------
	SpriteBatchName::Name batchName;

	void privDraw(Sprite * sprite);
};



#endif