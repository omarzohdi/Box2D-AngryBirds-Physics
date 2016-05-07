
#include "AzulCore.h"

#include "EnumName.h"
#include "TextMan.h"
#include "Text.h"
#include "Rect.h"
#include "Image.h"
#include "ImageMan.h"
#include "ScreenLineModel.h"
#include "ScreenLine.h"

//externs must be exterminated
extern GLShaderManager	shaderManager;

ScreenLine :: ScreenLine( SpriteBatchName::Name spriteBatchName, SpriteName::Name _spriteName, float _lineWidth, const Vect &_color, Vect2D &ptA,  Vect2D &ptB)
{
	this->setName( 0 );

	this->lineWidth = _lineWidth;
	this->color = _color;

	this->spriteName = _spriteName;

	ScreenLineModel *p = new ScreenLineModel( );
	this->screenLineModel = p;

	this->posA = ptA;
	this->posB = ptB;

	this->LocalToWorld.set(IDENTITY);
	this->ModelView.set(IDENTITY);

	SBNode *batch = SpriteBatchManager::Find(spriteBatchName);
	batch->addSprite( _spriteName, this);
}

// Constructor make sure everything is initialized
ScreenLine :: ScreenLine( const char * const _Name, ScreenLineModel * const p)
{
	this->screenLineModel = p;
	this->setName( _Name );

	this->LocalToWorld.set(IDENTITY);
	this->ModelView.set(IDENTITY);
};


void ScreenLine::transform( void )
{
	// create the origin in the lower left corner
	Matrix TransToOriginLowerLeft( TRANS, -WINDOWWIDTH/2, -WINDOWHEIGHT/2, 0.0f);


	// Create the local to world matrix (ie Model)
	this->LocalToWorld =  TransToOriginLowerLeft;
	                                    
	// Create the ModelView ( LocalToWorld * View)
	// Some pipelines have the project concatenated, others don't
	// Best to keep the separated, you can always join them with a quick multiply
   this->ModelView = this->LocalToWorld * Camera::getViewMatrix();

};


void ScreenLine::setRenderState( void )
{
	// Blends for sprites
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);

	// Use the stock shader
	Matrix mvp = ModelView * Camera::getProjMatrix();

	// flat shader
	shaderManager.UseStockShader(GLT_SCREEN_LINE, 
						& mvp, 
						& this->color);




			struct MyVertex_stride
			{
			float x;
			float y;
			float z;
			};


			const int numVerts = 2;
			MyVertex_stride pVerts[numVerts];


			pVerts[0].x = this->posA.x;
			pVerts[0].y = this->posA.y;
			pVerts[0].z = 0.0f;

			pVerts[1].x = this->posB.x;
			pVerts[1].y = this->posB.y;
			pVerts[1].z = 0.0f;
	
			/* Bind our first VBO as being the active buffer and storing vertex attributes (coordinates) */
			glBindBuffer(GL_ARRAY_BUFFER, this->screenLineModel->vbo);
 
			/* Copy the vertex data to our buffer */
			glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertex_stride) * numVerts, pVerts, GL_STATIC_COPY);


};

void ScreenLine::draw( void )
{  
	if( display )
	{
		glBindVertexArray(this->screenLineModel->vao);

		/*  render primitives from array data */
		glLineWidth(this->lineWidth);
		glDrawArrays(GL_LINES, 0, 2);

	}
};

void ScreenLine::privDraw()
{
	transform();
	setRenderState();
	draw();
}