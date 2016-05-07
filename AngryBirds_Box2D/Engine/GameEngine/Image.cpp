#include "ImageMan.h"
#include "Image.h"
#include "EnumName.h"
#include "Rect.h"
#include "Text.h"
#include "TextMan.h"

// public methods: -------------------------------------------------------------

Image::Image()
{
    this->imageName = ImageName::Not_Initialized;
    this->imageRect.clear();
    this->pText = 0;
}

void Image::Set(ImageName::Name _imageName, Text *_pText, Rect _rect)
{
    this->ManLink::Initialize();

    this->imageName = _imageName;
    this->pText = _pText;
    this->imageRect = _rect;
}

void Image::Set(ImageName::Name _imageName, TextName::Name _textName, Rect _rect)
{
    this->ManLink::Initialize();

    this->imageName = _imageName;
    this->pText = TextMan::Find(_textName);
    this->imageRect = _rect;
}

EnumName Image::getName()
{
	return ImageName( (EnumName::Name)this->imageName );
}