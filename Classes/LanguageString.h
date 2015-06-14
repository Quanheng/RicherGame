#ifndef __LANGUAGESTRING__H__
#define __LANGUAGESTRING__H__

#include "cocos2d.h"


USING_NS_CC;
class LanguageString
{

private:
	LanguageString();

public:
	static LanguageString* instance;
	static Dictionary *strings;
	~LanguageString();
	static LanguageString * getInstance();

	cocos2d::__String* getLanguageString(const char* strName);

};

#endif