#ifndef MAN_H
#define MAN_H

#include "ManLink.h"
#include "EnumName.h"

class Man // abstract
{
	
	// protected methods: -----------------------------------------------------------------------
protected:
	
	Man();

	// private: (reusable for other classes, just change types0: -----------------------------
private:

	void privReserveAddToFront( ManLink *node, ManLink *& head );
	ManLink *privReserveGetNodeFromFront( ManLink *& head );

protected:

    void privActiveRemoveNode(ManLink *node, ManLink *& head);
    void privActiveAddToFront(ManLink *node, ManLink *& head);

	
// private methods ------------------------------------------------------------------------------

protected:

    ManLink *privFind(EnumName _enumName);
    ManLink *privGetReserveObject();
    void privFillPool(int count);
    void privCreate(int _numReserve, int _reserveGrow);
    
// private: Data --------------------------------------------------------------------------------
	virtual ManLink *privGetNewObj() = 0;

protected:

	ManLink *active;
	ManLink *reserve;
	bool initalized;

	//  stats -------------------------------------------------------------------------------

	int totalNum;
	int reserveGrow;


};

#endif