#ifndef TRAIL_H
#define TRAIL_H

#include "GameSprite.h"

struct SmokeTrailNode
{
	GameSprite * pGamesprite;
	SmokeTrailNode * pnext;
	bool display;

	SmokeTrailNode()
		:pGamesprite (0), pnext(0), display(0)
	{}
};

class Trail
{
public:
	Trail(void);
	~Trail(void);

	SmokeTrailNode * Head;
	SmokeTrailNode * Tail;
	SmokeTrailNode * NextinLine;

	void AddNode( float ,float, bool );
	void DisableNodes();
	void DisplayNodes(float ,float, bool );

	int ActiveCount;
	int TotalCount;
};

#endif
