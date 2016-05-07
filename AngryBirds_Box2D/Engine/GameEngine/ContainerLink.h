#ifndef CONTAINERLINK_H
#define CONTAINERLINK_H

#include "EnumName.h"


class ContainerLink  // abstract class
{
public:
	ContainerLink();
	virtual ~ContainerLink();
	virtual EnumName getName() = 0;

protected: 
	virtual void Initialize();

public: 
	
	// Data: ------------------------
	ContainerLink *next;
	ContainerLink *prev;
};

#endif