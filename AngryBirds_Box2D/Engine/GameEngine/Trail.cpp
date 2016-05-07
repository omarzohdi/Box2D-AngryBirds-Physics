#include "Trail.h"


Trail::Trail(void)
	:Head(0), Tail(0), NextinLine(0), ActiveCount(0), TotalCount(0)
{}

void Trail::AddNode( float x, float y,bool large)
{
	large;
	SmokeTrailNode * newNode = new SmokeTrailNode();
	newNode->pGamesprite = new GameSprite(SpriteBatchName::SpriteBatch_Trail,  SpriteName::Sprite_SmokeRing, ImageName::Image_SmokeRing1, Rect(x, y, 10, 10) );
	newNode->display = true;
	TotalCount++;

	SmokeTrailNode * ptr = this->Tail;

	if (ptr != 0)
	{
		this->Tail->pnext = newNode;
		this->Tail = this->Tail->pnext;
	}
	else
	{
		this->Head = newNode;
		this->Tail = newNode;
	}

	this->NextinLine = newNode->pnext;

}
void Trail::DisplayNodes(float x,float y, bool large)
{
	if (NextinLine == 0)
		AddNode(x,y,large);
	else 
	{
		this->NextinLine->pGamesprite->enable();
		this->NextinLine->pGamesprite->spriteModel->destRect.x = x;
		this->NextinLine->pGamesprite->spriteModel->destRect.y = y;

		this->NextinLine->pGamesprite->posX = x;
		this->NextinLine->pGamesprite->posY= y;
		
		NextinLine->display = true;
		
		if (this->NextinLine == this->Tail)
			this->NextinLine = 0;
		else
			this->NextinLine = this->NextinLine->pnext;
	}

	ActiveCount++;
}
void Trail::DisableNodes()
{
	SmokeTrailNode * ptr = this->Head;

	while(ptr != 0)
	{
		if (ptr->display)
		{
			ptr->pGamesprite->disable();
			ptr->display = false;
			ActiveCount --;
		}
		
		ptr = ptr->pnext;


	}

	this->NextinLine = this->Head;

}


Trail::~Trail(void)
{
}
