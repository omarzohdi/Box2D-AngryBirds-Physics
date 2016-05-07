#ifndef SPRITE_MODEL_H
#define SPRITE_MODEL_H

#include "EnumName.h"
#include "Rect.h"
#include "GLTools.h"

class Image;

class SpriteModel
{

public:

	SpriteModel( ImageName::Name imageName, Rect destRect );
	bool SwapImage(ImageName::Name _imageName);

private:
	void privCreateVAO( Image &srcImage, Rect &destSprite);
	SpriteModel();

public:
	Image	*pImage;
	Rect	destRect;
	GLuint	vao;
	GLuint	textureID;
};

#endif