#ifndef SPRITE_BATCH_MAN_H
#define SPRITE_BATCH_MAN_H

#include "Man.h"
#include "EnumName.h"
#include "Rect.h"
#include "SBNode.h"
class SBNode;

class SpriteBatchManager : public Man
{
public:
    static void Create(int _numReserve = 3, int _reserveGrow = 1);
	static void AddBatch(SpriteBatchName::Name batchName);
	static SBNode *Find(SpriteBatchName::Name _batchName);

	static void Process();
	   
protected:

	ManLink *SpriteBatchManager::privGetNewObj();



private: 

	static SpriteBatchManager *privInstance();
	SpriteBatchManager();


};



#endif