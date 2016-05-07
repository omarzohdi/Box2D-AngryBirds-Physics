
#include "AzulCore.h"
#include "EnumName.h"
#include "TextMan.h"
#include "Text.h"
#include "Rect.h"
#include "Image.h"
#include "ImageMan.h"
#include "BoxModel.h"

BoxModel::BoxModel( Rect _destRect )
{	
	this->destRect = _destRect;

	this->privCreateVAO( this->destRect );
}


void BoxModel::privCreateVAO( Rect &destSprite )
{
	float md_local_begin_x = -destSprite.width * 0.5f;
	float md_local_begin_y = -destSprite.height * 0.5f;
	float md_local_end_x = destSprite.width * 0.5f;
	float md_local_end_y = destSprite.height * 0.5f;

	struct MyVertex_stride
	{
		float x;
		float y;
		float z;
	};

	MyVertex_stride pVerts[4];

	// bottom Left
	pVerts[0].x = md_local_begin_x;
	pVerts[0].y = md_local_begin_y;
	pVerts[0].z = 0.0f;

	// top Left
	pVerts[1].x = md_local_begin_x;
	pVerts[1].y = md_local_end_y;
	pVerts[1].z = 0.0f;

	// top Right
	pVerts[2].x = md_local_end_x;
	pVerts[2].y = md_local_end_y;
	pVerts[2].z = 0.0f;

	// bottom Right
	pVerts[3].x = md_local_end_x;
	pVerts[3].y = md_local_begin_y;
	pVerts[3].z = 0.0f;

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
		glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertex_stride) * 4, pVerts, GL_STATIC_DRAW);
		
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




