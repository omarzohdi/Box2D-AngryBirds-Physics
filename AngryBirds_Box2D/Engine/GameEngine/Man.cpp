#include "Man.h"
#include "ManLink.h"
#include <assert.h>


// public methods: -----------------------------------------------------------------------
Man:: Man()
{
    this->active = 0;
    this->reserve = 0;
    this->initalized = false;
    this->totalNum = 0;
    this->reserveGrow = 0;
}

// private: (reusable for other classes, just change types0: ------------------------------------

void Man::privReserveAddToFront(ManLink *node, ManLink *&head)
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

ManLink *Man::privReserveGetNodeFromFront(ManLink *&head)
{
    assert(head != 0);

    ManLink *node = head;
    head = node->next;
    if (node->next != 0)
    {
        node->next->prev = node->prev;
    }
    return node;
}

void Man::privActiveRemoveNode(ManLink *node, ManLink *&head)
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

void Man::privActiveAddToFront(ManLink *node, ManLink *&head)
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

// private methods ------------------------------------------------------------------------------

ManLink *Man::privFind(EnumName _enumName)
{
    // // Do we need to get more Images?
    ManLink *pLink = this->active;

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

ManLink *Man::privGetReserveObject()
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
    ManLink *pObj = this->privReserveGetNodeFromFront(this->reserve);

    return pObj;
}

void Man::privFillPool(int count)
{
    // add to the count
    this->totalNum += count;

    // allocate Objects
    for (int i = 0; i < count; i++)
    {
        // create a new Object
        ManLink *pObj = privGetNewObj();
        // move it to InActive list
        privReserveAddToFront(pObj, this->reserve);
    }
}

void Man::privCreate(int _numReserve, int _reserveGrow)
{
    //Debug.WriteLine("{0}:Create(): reserve:{1} delta:{2}", this, _numReserve, _reserveGrow);

    // only initialize once
    assert(this->initalized == false);

    // Set variables
    this->initalized = true;
    this->reserveGrow = _reserveGrow;

    // OK now preload Nodes
    this->privFillPool(_numReserve);
}


