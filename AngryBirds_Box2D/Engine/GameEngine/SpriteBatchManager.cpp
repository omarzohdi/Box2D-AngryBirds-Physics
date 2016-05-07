#include "SpriteBatchManager.h"
#include "SpriteBatch.h"
#include "EnumName.h"

void SpriteBatchManager::Create(int _numReserve, int _reserveGrow)
{
	privInstance()->privCreate(_numReserve, _reserveGrow);
}

void SpriteBatchManager::AddBatch( SpriteBatchName::Name _batchName)
{
	SpriteBatchManager *sMan = privInstance();

	SpriteBatch * batch = new SpriteBatch();
	batch->Set(_batchName);

	SBNode *  node = (SBNode *)sMan->privGetReserveObject();
	node->Set(_batchName, batch);

	sMan->privActiveAddToFront((ManLink *)node, sMan->active);
}

SBNode * SpriteBatchManager::Find(SpriteBatchName::Name _batchName)
{
	return (SBNode *) privInstance()->privFind( SpriteBatchName((EnumName::Name)_batchName) );
}

ManLink * SpriteBatchManager::privGetNewObj()
{
	ManLink * pObj = new SBNode();
	return pObj;
}

SpriteBatchManager * SpriteBatchManager::privInstance()
{
	static SpriteBatchManager instance;
	return &instance;
}

SpriteBatchManager::SpriteBatchManager()
{

}

void SpriteBatchManager::Process()
{
	SpriteBatchManager *sMan = privInstance();

	ManLink * ptr = sMan->active;

	while(ptr != 0)
	{
		((SBNode *)ptr)->privDraw();

		ptr = ptr->next;
	}
}

