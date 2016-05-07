#include <string>
#include <assert.h>

#include "TextMan.h"
#include "Text.h"




void TextMan::Create(int _numReserve, int _reserveGrow)
{
    // Create Manager
    TextMan::privInstance()->privCreate(_numReserve, _reserveGrow);
}

void TextMan::Load(TextType _type, TextName::Name _enumName, std::string _assetName)
{
    // Get the instance
    TextMan *pMan = TextMan::privInstance();

    // Get a Object off the list
    Text *pText = (Text *)pMan->privGetReserveObject();

	bool result = false;

    // Initialize object
    switch (_type)
    {
		case TextType::Text2D:

			glGenTextures(1, &pText->glTextData.textID);
			glBindTexture(pText->glTextData.target, pText->glTextData.textID);

			memcpy_s(&pText->glTextData.textName[0], TEXTURE_NAME_SIZE2,_assetName.c_str(),TEXTURE_NAME_SIZE2-1);

			result = pText->LoadTGATexture(_assetName.c_str(), GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
			assert(result);

			pText->assetName = _assetName;
			pText->textName = _enumName;
			pText->height = pText->glTextData.height;
			pText->width = pText->glTextData.width;
			pText->type = _type;
		

            break;
		default:
			assert(false);
			break;
	}

    // Attach object to active list
    pMan->privActiveAddToFront( (ManLink *)pText, pMan->active );
}


Text *TextMan::Find(TextName::Name _name)
{
    // Find the object
    return (Text *)privInstance()->privFind( TextName( (EnumName::Name)_name ) );
}

ManLink *TextMan::privGetNewObj()
{
    ManLink *pObj =  new Text();
    return pObj;
}

TextMan *TextMan::privInstance()
{
	// This is where its actually stored (BSS section)
	static TextMan instance;
	return &instance;
}

TextMan::TextMan()
{

}


