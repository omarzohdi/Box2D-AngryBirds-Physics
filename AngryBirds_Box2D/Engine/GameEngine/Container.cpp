#include "Container.h"
#include "ContainerLink.h"
#include <assert.h>


Container::Container()
{
	this->active = 0;
    this->reserve = 0;
    this->initalized = false;
    this->totalNum = 0;
    this->reserveGrow = 0;
}

void Container::privReserveAddToFront(ContainerLink *node, ContainerLink *&head)
{
    assert(node != 0);

    if (head == 0)
    {
        head = node;
        node->next = 0;
        node->prev = 0;
    }
    else
    {
        node->next = head;
        head->prev = node;
        head = node;
    }
}

ContainerLink *Container::privReserveGetNodeFromFront(ContainerLink *&head)
{
    assert(head != 0);

    ContainerLink *node = head;
    head = node->next;
    if (node->next != 0)
    {
        node->next->prev = node->prev;
    }
    return node;
}

void Container::privActiveRemoveNode(ContainerLink *node, ContainerLink *&head)
{
    if (node->prev != 0)
    {	// middle or last node
        node->prev->next = node->next;
    }
    else
    {  // first
        head = node->next;
    }

    if (node->next != 0)
    {	// middle node
        node->next->prev = node->prev;
    }
}

void Container::privActiveAddToFront(ContainerLink *node, ContainerLink *&head)
{
    assert(node != 0);

    if (head == 0)
    {
        head = node;
        node->next = 0;
        node->prev = 0;
    }
    else
    {
        node->next = head;
        head->prev = node;
        head = node;
    }
}

ContainerLink *Container::privFind(EnumName _enumName)
{
    // // Do we need to get more Images?
    ContainerLink *pLink = this->active;

    while (pLink != 0)
    {
        if (pLink->getName() == _enumName)
        {
            break;
        }
        pLink = pLink->next;
    }

    return pLink;
}

ContainerLink *Container::privGetReserveObject()
{
    if (this->reserve == 0)
    {
        // fill pool with more nodes
        // OK now preload the timeEvents
        this->privFillPool(this->reserveGrow);
    }

    // make sure we have TimeEvents

    assert(this->reserve != 0);

    // Detach 1 Image from the pool
    ContainerLink *pObj = this->privReserveGetNodeFromFront(this->reserve);

    return pObj;
}

void Container::privFillPool(int count)
{
    // add to the count
    this->totalNum += count;

    // allocate Objects
    for (int i = 0; i < count; i++)
    {
        // create a new Object
        ContainerLink *pObj = privGetNewObj();
        // move it to InActive list
        privReserveAddToFront(pObj, this->reserve);
    }
}

void Container::privCreate(int _numReserve, int _reserveGrow)
{
    // only initialize once
    assert(this->initalized == false);

    // Set variables
    this->initalized = true;
    this->reserveGrow = _reserveGrow;

    // OK now preload Nodes
    this->privFillPool(_numReserve);
}

EnumName Container::getName()
{
	return this->containerName;
}