
#include "AzulCore.h"

#include "EnumName.h"
#include "TextMan.h"
#include "Text.h"
#include "Rect.h"
#include "Image.h"
#include "ImageMan.h"

//externs must be exterminated
extern GLShaderManager	shaderManager;



GameSprite :: GameSprite( SpriteBatchName::Name spriteBatchName, SpriteName::Name _spriteName, ImageName::Name imageName, Rect destRect)
{
	this->setName( 0 );

	this->spriteName = _spriteName;

	SpriteModel *p = new SpriteModel( imageName, destRect );
	this->spriteModel = p;

	this->angle = 0.0f;

	this->origWidth = p->destRect.width;
	this->origHeight = p->destRect.height;

	this->posX = p->destRect.x;
	this->posY = p->destRect.y;

	this->scaleX = 1.0f;
	this->scaleY = 1.0f;

	this->LocalToWorld.set(IDENTITY);
	this->ModelView.set(IDENTITY);

	SBNode *batch = SpriteBatchManager::Find(spriteBatchName);
	assert( batch != 0 );
	batch->addSprite( _spriteName, this);

}

// Constructor make sure everything is initialized
GameSprite :: GameSprite( const char * const _Name, SpriteModel * const p)
{
	this->spriteModel = p;
	this->setName( _Name );

	this->angle = 0.0f;

	this->origWidth = p->destRect.width;
	this->origHeight = p->destRect.height;

	this->posX = p->destRect.x;
	this->posY = p->destRect.y;

	this->scaleX = 1.0f;
	this->scaleY = 1.0f;

	this->LocalToWorld.set(IDENTITY);
	this->ModelView.set(IDENTITY);
};


void GameSprite::transform( void )
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


void GameSprite::setRenderState( void )
{
	// Blends for sprites
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);

	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, this->spriteModel->textureID);

	// Use the stock shader
	shaderManager.UseStockShader(GLT_SHADER_SPRITE, 
								&ModelView,
								&Camera::getProjMatrix(), 
								0);

};

void GameSprite::draw( void )
{
	if( display )
	{
		glBindVertexArray(this->spriteModel->vao);

		/*  render primitives from array data */
		// (GLenum  mode,  GLsizei  count,  GLenum  type,  const GLvoid *  indices);
		glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_SHORT, 0);   //The starting point of the IBO
	}

};


void GameSprite::privDraw()
{
	transform();
	setRenderState();
	draw();
}