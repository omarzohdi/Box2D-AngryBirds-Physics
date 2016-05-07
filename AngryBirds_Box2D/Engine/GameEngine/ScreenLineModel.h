#ifndef SCREEN_LINE_MODEL_H
#define SCREEN_LINE_MODEL_H

#include "EnumName.h"
#include "Rect.h"
#include "Vect2D.h"


class ScreenLineModel
{

public:

	ScreenLineModel( );

private:
	void privCreateVAO( );


public:
	GLuint	vao;
	GLuint	vbo;

};

#endif