#include "ImageMan.h"
#include "Image.h"
#include "EnumName.h"


void ImageMan::Create(int _numReserve, int _reserveGrow)
{
	// Create Manager
	privInstance()->privCreate(_numReserve, _reserveGrow);
}


void ImageMan::Add(ImageName::Name _imageName, TextName::Name _textName, Rect imageRect)
{
    // Get the instance
    ImageMan *pMan = privInstance();

    // Get a Object off the list
    Image *pImage = (Image *)pMan->privGetReserveObject();

    // Initialize object
    pImage->Set( _imageName, _textName, imageRect );

    // Attach object to active list
    pMan->privActiveAddToFront((ManLink *)pImage,pMan->active);
}



Image *ImageMan::Find(ImageName::Name _ImageName)
{
    // Find the object
    return (Image *) privInstance()->privFind( ImageName((EnumName::Name)_ImageName) );
}

ManLink *ImageMan::privGetNewObj()
{
    ManLink *pObj =  new Image();
    return pObj;
}

ImageMan *ImageMan::privInstance()
{
	// This is where its actually stored (BSS section)
	static ImageMan instance;
	return &instance;
}

ImageMan::ImageMan()
{

}