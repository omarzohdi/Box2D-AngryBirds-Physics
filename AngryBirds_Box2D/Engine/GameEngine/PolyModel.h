#ifndef POLY_MODEL_H
#define POLY_MODEL_H

#include "EnumName.h"
#include "Rect.h"
#include "Vect2D.h"


class PolyModel
{

public:

	PolyModel( Vect2D originPt, int numVerts, Vect2D *vertList);

private:
	void privCreateVAO( Vect2D originPt, int numVerts, Vect2D *vertList);
	PolyModel();

public:

	Vect2D originPt;
	int numVerts;
	Vect2D *vertList;
	GLuint	vao;

};

#endif