#ifndef BOX_MODEL_H
#define BOX_MODEL_H

#include "EnumName.h"
#include "Rect.h"
class Image;

class BoxModel
{

public:

	BoxModel( Rect destRect );

private:
	void privCreateVAO( Rect &destSprite);
	BoxModel();

public:

	Rect	destRect;
	GLuint	vao;

};

#endif