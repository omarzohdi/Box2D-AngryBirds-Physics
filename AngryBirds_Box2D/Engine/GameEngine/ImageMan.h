#ifndef IMAGE_MAN_H
#define IMAGE_MAN_H

#include "Man.h"
#include "EnumName.h"
#include "Rect.h"
class Image;

class ImageMan: public Man
{
public:
    static void Create(int _numReserve = 3, int _reserveGrow = 1);
    static void Add(ImageName::Name imageName, TextName::Name textName, Rect imageRect );
    static Image *Find(ImageName::Name _imageName);
	   
protected:

	ManLink *ImageMan::privGetNewObj();

private: 

	static ImageMan *privInstance();
	ImageMan();


};



#endif