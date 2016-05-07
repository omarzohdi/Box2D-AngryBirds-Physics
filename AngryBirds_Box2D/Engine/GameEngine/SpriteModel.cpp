
#include "AzulCore.h"
#include "EnumName.h"
#include "TextMan.h"
#include "Text.h"
#include "Rect.h"
#include "Image.h"
#include "ImageMan.h"

bool SpriteModel::SwapImage(ImageName::Name _imageName)
{
	bool status = false;

	Image *pNewImage = ImageMan::Find( _imageName );

	if( pNewImage != 0 )
	{
		status = true;
		this->pImage = pNewImage;

		// OK this is more difficult than I thought.
		// Need to unload the VAO, then recreate the VAO with new model
		this->privCreateVAO( *pImage, this->destRect );
	}
	else
	{
		// your image is wrong
		assert(0);
	}

	return status;
}


SpriteModel::SpriteModel( ImageName::Name _imageName, Rect _destRect )
{	
	this->pImage = ImageMan::Find( _imageName );
	assert( this->pImage );
	this->textureID = pImage->pText->glTextData.textID;
	this->destRect = _destRect;

	this->privCreateVAO( *pImage, this->destRect );
}


void SpriteModel::privCreateVAO( Image &srcImage, Rect &destSprite)
{

	Text *pText = TextMan::Find( srcImage.pText->textName );

	float st_begin_x = srcImage.imageRect.x / pText->width;
	float st_begin_y = srcImage.imageRect.y / pText->height;

	float st_end_x = (srcImage.imageRect.x + srcImage.imageRect.width )/ pText->width;
	float st_end_y = (srcImage.imageRect.y + srcImage.imageRect.height )/ pText->height;

	float md_local_begin_x = -destSprite.width * 0.5f;
	float md_local_begin_y = -destSprite.height * 0.5f;
	float md_local_end_x = destSprite.width * 0.5f;
	float md_local_end_y = destSprite.height * 0.5f;

struct MyVertex_stride
{
	float x;
	float y;
	float z;
	float s;
	float t;
};

struct MyTriList
{
	unsigned short v1;
	unsigned short v2;
	unsigned short v3;
};


MyTriList	tlist[2];
MyVertex_stride pVerts[4];

// front
tlist[0].v1 = 0;
tlist[0].v2 = 1;
tlist[0].v3 = 2;

tlist[1].v1 = 2;
tlist[1].v2 = 3;
tlist[1].v3 = 0;


// bottom Left
pVerts[0].x = md_local_begin_x;
pVerts[0].y = md_local_begin_y;
pVerts[0].z = 0.0f;

pVerts[0].s = st_begin_x;
pVerts[0].t = st_end_y;


// top Left
pVerts[1].x = md_local_begin_x;
pVerts[1].y = md_local_end_y;
pVerts[1].z = 0.0f;

pVerts[1].s = st_begin_x;
pVerts[1].t = st_begin_y;

// top Right
pVerts[2].x = md_local_end_x;
pVerts[2].y = md_local_end_y;
pVerts[2].z = 0.0f;

pVerts[2].s = st_end_x;
pVerts[2].t = st_begin_y;

// bottom Right
pVerts[3].x = md_local_end_x;
pVerts[3].y = md_local_begin_y;
pVerts[3].z = 0.0f;

pVerts[3].s = st_end_x;
pVerts[3].t = st_end_y;





     /* Allocate and assign a Vertex Array Object to our handle */
    glGenVertexArrays(1, &this->vao);
 
    /* Bind our Vertex Array Object as the current used object */
    glBindVertexArray(this->vao);

    //GLuint vbo;
    GLuint vbo[2];

    /* Allocate and assign two Vertex Buffer Objects to our handle */
    glGenBuffers(2, vbo);
 
    // Load the combined data: ---------------------------------------------------------

		      /* Bind our first VBO as being the active buffer and storing vertex attributes (coordinates) */
		      glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
 
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
		 
 
    // Texture data: ---------------------------------------------------------
     
				// Set Attribute to 3
            //           WHY - 3? and not 1,2,3 (this is tied to the shader attribute, it is defined in GLShaderManager.h)
            //           GLT_ATTRIBUTE_TEXTURE0 = 3

            // Specifies the index of the generic vertex attribute to be enabled
		      glEnableVertexAttribArray(3);  

		      /* Specify that our coordinate data is going into attribute index 3, and contains 2 floats per vertex */
            // ( GLuint index,  GLint size,  GLenum type,  GLboolean normalized,  GLsizei stride,  const GLvoid * pointer);
            void *offsetTex = (void *)((unsigned int)&pVerts[0].s - (unsigned int)pVerts);
		      glVertexAttribPointer(3, 2, GL_FLOAT,  GL_FALSE, sizeof(MyVertex_stride), offsetTex);


      // Normal data: ---------------------------------------------------------
		
				//// Set Attribute to 2
    //        //           WHY - 2? and not 1,2,3 (this is tied to the shader attribute, it is defined in GLShaderManager.h)
    //        //           GLT_ATTRIBUTE_NORMAL = 2

    //        // Specifies the index of the generic vertex attribute to be enabled
		  //    glEnableVertexAttribArray(2);  

		  //    /* Specify that our coordinate data is going into attribute index 3, and contains 2 floats per vertex */
    //        // ( GLuint index,  GLint size,  GLenum type,  GLboolean normalized,  GLsizei stride,  const GLvoid * pointer);
    //        void *offsetNorm = (void *)((unsigned int)&pVerts[0].nx - (unsigned int)pVerts);
		  //    glVertexAttribPointer(2, 3, GL_FLOAT,  GL_FALSE, sizeof(MyVertex_stride), offsetNorm);
		 

      // Load the index data: ---------------------------------------------------------
	

            /* Bind our 2nd VBO as being the active buffer and storing index ) */
		      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

	         /* Copy the index data to our buffer */
            // glBufferData(type, size in bytes, data, usage) 
		      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(MyTriList)*6, tlist, GL_STATIC_DRAW);


}




