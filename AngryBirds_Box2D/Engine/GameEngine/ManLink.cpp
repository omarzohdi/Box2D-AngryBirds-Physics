#include "ManLink.h"
#include "EnumName.h"

ManLink::ManLink()
{
    this->Initialize();
}

ManLink::~ManLink()
{
    
}

void ManLink::Initialize()
{
    this->next = 0;
    this->prev = 0;
}
