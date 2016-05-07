#ifndef TEXT_H
#define TEXT_H

#include "AzulCore.h"

#include <string>
#include "ManLink.h"
#include "EnumName.h"



enum TextType{
    Text2D,
    No_TYPE
};


#define TEXTURE_NAME_SIZE2  64 

struct TextData
{
   TextData()
   {
		width  = -1;
		height = -1;
		memset(textName,0,TEXTURE_NAME_SIZE2);

		minFilter = GL_LINEAR;
		magFilter = GL_LINEAR;
		wrapMode  =	GL_CLAMP_TO_EDGE;

		target = GL_TEXTURE_2D;
		textID = 0;
   }

   GLuint		textID;
   char			textName[ TEXTURE_NAME_SIZE2 ]; 
   int			width;
   int			height;
   GLenum		target;     // texture target
   GLenum		minFilter;  // min/mag filters
   GLenum		magFilter;
   GLenum		wrapMode;   // texture wrap moode
};


class Text: public ManLink
{

public: 
	Text();

	void Set(TextType _type, TextName::Name _textName, std::string _assetName);
 
   EnumName getName();

   bool LoadTGATexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode);


public:
    // data

	std::string assetName;
    TextName::Name	textName;
    int			height;
    int			width;
    TextType	type;

	TextData	glTextData;

};


#endif