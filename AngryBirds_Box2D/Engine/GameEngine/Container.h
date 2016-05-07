#ifndef CONTAINER_H
#define CONTAINER_H

#include "ManLink.h"
#include "ContainerLink.h"
#include "EnumName.h"

class Container : public ManLink
{
public:
	EnumName getName();
	EnumName containerName;

protected:
	Container();

private:
	void privReserveAddToFront( ContainerLink *node, ContainerLink *& head );
	ContainerLink *privReserveGetNodeFromFront( ContainerLink *& head );

protected:
	void privActiveRemoveNode(ContainerLink *node, ContainerLink *& head);
    void privActiveAddToFront(ContainerLink *node, ContainerLink *& head);

protected:
	ContainerLink *privFind(EnumName _enumName);
    ContainerLink *privGetReserveObject();
    void privFillPool(int count);
    void privCreate(int _numReserve, int _reserveGrow);

	virtual ContainerLink *privGetNewObj() = 0;

protected:
	ContainerLink *active;
	ContainerLink *reserve;
	bool initalized;

	//  stats -------------------------------------------------------------------------------

	int totalNum;
	int reserveGrow;
};



#endif