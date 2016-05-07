#include "ContainerLink.h"
#include "EnumName.h"

ContainerLink::ContainerLink()
{
    this->Initialize();
}

ContainerLink::~ContainerLink()
{
    
}

void ContainerLink::Initialize()
{
    this->next = 0;
    this->prev = 0;
}