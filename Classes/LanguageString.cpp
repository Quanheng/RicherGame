#include "LanguageString.h"

LanguageString* LanguageString::instance;
Dictionary * LanguageString::strings;

LanguageString::LanguageString()
{
}


LanguageString::~LanguageString()
{
	strings->autorelease();
}

LanguageString * LanguageString::getInstance()
{
	if(instance == NULL)
	{
		instance = new LanguageString();
	}
	
	return instance;
}

__String* LanguageString::getLanguageString(const char* strName)
	{
		LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();

		if(strings == NULL)
		{
			switch (currentLanguageType)
			{
			case kLanguageEnglish:  //系统是英文，则加载string_en.plist文件
				{
					strings = Dictionary::createWithContentsOfFile("fonts/string_en.plist"); 
					strings->retain();
					break;
				}

			case kLanguageChinese:    //系统是中文，则加载string_zh.plist文件
				{
					strings = Dictionary::createWithContentsOfFile("fonts/string_zh.plist");
					strings->retain();
					break;
				}

			}
		}
		__String* retStr = static_cast<__String*>(strings->objectForKey(strName));
		return retStr;

	}