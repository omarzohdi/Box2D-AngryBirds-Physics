#ifndef SPRITE_H
#define SPRITE_H

#include "GraphicsObject.h"

class Sprite : public GraphicsObject
{
public:

	void Draw();

	Sprite();
	~Sprite();

	void update();

	// These are pure virtual, needed to be defined by the derived class
	virtual void transform( void ) = 0;   
	virtual void draw(void) = 0;
	virtual void setRenderState(void) = 0;
	bool getDisplay();
	bool display;

	void enable();
	void disable();

private:


};

#endif