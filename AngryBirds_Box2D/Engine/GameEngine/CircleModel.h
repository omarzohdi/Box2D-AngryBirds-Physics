#ifndef CIRCLE_MODEL_H
#define CIRCLE_MODEL_H

#include "EnumName.h"
#include "Rect.h"
class Image;

class CircleModel
{

public:

	CircleModel( Rect destRect );

private:
	void privCreateVAO( Rect &destSprite);
	CircleModel();

public:

	Rect	destRect;
	GLuint	vao;

};

#endif