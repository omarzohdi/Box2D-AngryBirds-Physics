#ifndef MANLINK_H
#define MANLINK_H

#include "EnumName.h"


class ManLink  // abstract class
{
public:
	ManLink();
	virtual ~ManLink();
	virtual EnumName getName() = 0;

protected: 
	virtual void Initialize();

public: 
	
	// Data: ------------------------
	ManLink *next;
	ManLink *prev;

};

#endif