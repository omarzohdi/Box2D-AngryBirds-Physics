#ifndef IMAGE_H
#define IMAGE_H

#include "Rect.h"
#include "Text.h"

 
class Image: public ManLink
{
       
public:
	// public methods: -------------------------------------------------------------
	Image();
	void Set(ImageName::Name imageName, Text *pText, Rect rect);
	void Set(ImageName::Name imageName, TextName::Name textName, Rect rect);
	EnumName getName();
public:

	// data: -----------------------------------------------------------------------

	ImageName::Name	imageName;
	Rect		imageRect;
	Text		*pText;

};




#endif