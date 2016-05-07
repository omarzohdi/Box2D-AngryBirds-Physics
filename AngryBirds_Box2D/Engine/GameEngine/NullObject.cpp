#include "AzulCore.h"


NullObject::NullObject(const char * const _Name)
{
   // initialize the name
   this->setName( _Name );
}
	
// must define, base class has abstract methods
void NullObject::transform( void )
{
}

void NullObject::draw( void )
{
}

void NullObject::setRenderState(void)
{
}
