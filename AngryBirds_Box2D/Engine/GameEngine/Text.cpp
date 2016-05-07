#include "Text.h"

Text::Text()
{
    this->assetName.clear();
	this->textName = TextName::Not_Initialized;
    this->height = -1;
    this->width = -1;
    this->type = TextType::No_TYPE;
}


void Text::Set(TextType _type, TextName::Name _textName, std::string _assetName)
{
	ManLink::Initialize();

    this->assetName = _assetName;
    this->textName = _textName;
    this->height = -1;
    this->width = -1;
    this->type = _type;
}

EnumName Text::getName()
{
	return TextName( (EnumName::Name)this->textName );
}

// Load a TGA as a 2D Texture. Completely initialize the state
bool Text::LoadTGATexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
	GLbyte *pBits;
	int nWidth, nHeight, nComponents;
	GLenum eFormat;
	
	// Read the texture bits
	pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponents, &eFormat);
	if(pBits == NULL) 
		return false;
	
	this->glTextData.height = nHeight;
	this->glTextData.width = nWidth;
	this->glTextData.magFilter = magFilter;
	this->glTextData.minFilter = minFilter;
	this->glTextData.wrapMode = wrapMode;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0,
				 eFormat, GL_UNSIGNED_BYTE, pBits);
	
    free(pBits);

	return true;
}
