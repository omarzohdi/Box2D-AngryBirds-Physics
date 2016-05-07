#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include "MathEngine.h"
#include "PCSNode.h"

class GraphicsObject : public PCSNode
{
public:
	 
	GraphicsObject()
	{
		LocalToWorld.set(IDENTITY);
		ModelView.set(IDENTITY);
	};

	// These are pure virtual, needed to be defined by the derived class
	virtual void transform( void ) = 0;   
	virtual void draw(void) = 0;
	virtual void setRenderState(void) = 0;

	Matrix &getWorld()
	{
		return this->LocalToWorld;

	}
protected:
	Matrix	LocalToWorld;
	Matrix	ModelView;

	
};

#endif