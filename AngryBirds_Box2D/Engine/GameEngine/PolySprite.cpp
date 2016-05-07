
#include "AzulCore.h"

#include "EnumName.h"
#include "TextMan.h"
#include "Text.h"
#include "Rect.h"
#include "Image.h"
#include "ImageMan.h"
#include "PolyModel.h"
#include "PolySprite.h"

//externs must be exterminated
extern GLShaderManager	shaderManager;

PolySprite :: PolySprite( SpriteBatchName::Name spriteBatchName, SpriteName::Name _spriteName, float _lineWidth, const Vect &_color, Vect2D originPt, int numVerts, Vect2D *vertList, LineType _type)
{
	this->setName( 0 );

	this->lineWidth = _lineWidth;
	this->color = _color;

	this->spriteName = _spriteName;

	PolyModel *p = new PolyModel( originPt, numVerts, vertList);
	this->polyModel = p;

	this->angle = 0.0f;

	this->posX = p->originPt.x;
	this->posY = p->originPt.y;

	this->scaleX = 1.0f;
	this->scaleY = 1.0f;

	this->type = _type;

	this->LocalToWorld.set(IDENTITY);
	this->ModelView.set(IDENTITY);

	SBNode *batch = SpriteBatchManager::Find(spriteBatchName);
	batch->addSprite( _spriteName, this);
}

// Constructor make sure everything is initialized
PolySprite :: PolySprite( const char * const _Name, PolyModel * const p)
{
	this->polyModel = p;
	this->setName( _Name );

	this->angle = 0.0f;

	this->posX = p->originPt.x;
	this->posY = p->originPt.y;

	this->scaleX = 1.0f;
	this->scaleY = 1.0f;

	this->LocalToWorld.set(IDENTITY);
	this->ModelView.set(IDENTITY);
};


void PolySprite::transform( void )
{

	// create the tranformation matrices
	Matrix Scale(SCALE, this->scaleX, this->scaleY, 1.0f);
	Matrix RotZ( ROT_Z, angle );
	Matrix Trans( TRANS, this->posX, this->posY, 0.0f);

	// create the origin in the lower left corner
	Matrix TransToOriginLowerLeft( TRANS, -WINDOWWIDTH/2, -WINDOWHEIGHT/2, 0.0f);


	// Create the local to world matrix (ie Model)
	this->LocalToWorld =  Scale * RotZ * Trans * TransToOriginLowerLeft;
	                                    
	// Create the ModelView ( LocalToWorld * View)
	// Some pipelines have the project concatenated, others don't
	// Best to keep the separated, you can always join them with a quick multiply
   this->ModelView = this->LocalToWorld * Camera::getViewMatrix();

};


void PolySprite::setRenderState( void )
{
	// Blends for sprites
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);

	// Use the stock shader
	Matrix mvp = ModelView * Camera::getProjMatrix();

	// flat shader
	shaderManager.UseStockShader(GLT_SHADER_FLAT, 
						& mvp, 
						& this->color);

};

void PolySprite::draw( void )
{  
	if( display )
	{
		glBindVertexArray(this->polyModel->vao);

		/*  render primitives from array data */
		glLineWidth(this->lineWidth);
		glDrawArrays(this->type, 0, this->polyModel->numVerts);

	}
};

void PolySprite::privDraw()
{
	transform();
	setRenderState();
	draw();
}