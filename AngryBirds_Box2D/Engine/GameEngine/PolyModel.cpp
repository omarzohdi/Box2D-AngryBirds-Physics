
#include "AzulCore.h"
#include "EnumName.h"
#include "TextMan.h"
#include "Text.h"
#include "Rect.h"
#include "Image.h"
#include "ImageMan.h"
#include "PolyModel.h"

PolyModel::PolyModel( Vect2D originPt, int numVerts, Vect2D *vertList)
{	
	this->originPt = originPt;
	this->numVerts = numVerts;

	// copy a deep copy
	this->vertList = vertList;

	// needs to happen for a circle
	assert( vertList != 0 );
	assert( numVerts >= 3 );
	this->privCreateVAO( originPt, numVerts, vertList);
}


void PolyModel::privCreateVAO( Vect2D originPt, int numVerts, Vect2D *vertList)
{
	vertList;
	originPt;
	struct MyVertex_stride
	{
		float x;
		float y;
		float z;
	};

	assert( numVerts <= 8 );
	
	MyVertex_stride pVerts[8];

	
	for( int i = 0; i < numVerts; i++ )
	{
		pVerts[i].x = vertList[i].x;
		pVerts[i].y = vertList[i].y;
		pVerts[i].z = 0.0f;
	}


     /* Allocate and assign a Vertex Array Object to our handle */
    glGenVertexArrays(1, &this->vao);
 
    /* Bind our Vertex Array Object as the current used object */
    glBindVertexArray(this->vao);

    GLuint vbo;

    /* Allocate and assign two Vertex Buffer Objects to our handle */
    glGenBuffers(1, &vbo);
 
    // Load the combined data: ---------------------------------------------------------

		/* Bind our first VBO as being the active buffer and storing vertex attributes (coordinates) */
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
 
		/* Copy the vertex data to our buffer */
		// glBufferData(type, size in bytes, data, usage) 
		glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertex_stride) * numVerts, pVerts, GL_STATIC_DRAW);
		
   // VERTEX data: ---------------------------------------------------------

		// Set Attribute to 0
		//           WHY - 0? and not 1,2,3 (this is tied to the shader attribute, it is defined in GLShaderManager.h)
		//           GLT_ATTRIBUTE_VERTEX = 0

		// Specifies the index of the generic vertex attribute to be enabled
		glEnableVertexAttribArray(0);  

		/* Specify that our coordinate data is going into attribute index 0, and contains 3 floats per vertex */
		// ( GLuint index,  GLint size,  GLenum type,  GLboolean normalized,  GLsizei stride,  const GLvoid * pointer);
		void *offsetVert = (void *)((unsigned int)&pVerts[0].x - (unsigned int)pVerts);
		glVertexAttribPointer(0, 3, GL_FLOAT,  GL_FALSE, sizeof(MyVertex_stride), offsetVert);
		 
}




