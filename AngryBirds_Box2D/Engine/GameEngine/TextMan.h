#ifndef TEXTMAN_H
#define TEXTMAN_H

#include <string>
#include "Man.h"
#include "Text.h"


class TextMan : public Man
{

public:
	
	static void Create(int _numReserve = 3, int _reserveGrow = 1);
	static void Load(TextType _type, TextName::Name _enumName, std::string _assetName);
	static Text *Find(TextName::Name _name);

protected:
	virtual ManLink *privGetNewObj();

private:
    static TextMan *privInstance();
    TextMan();
 
private:
    // Data
};

#endif