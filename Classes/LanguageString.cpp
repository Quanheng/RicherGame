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
			case kLanguageEnglish:  //ϵͳ��Ӣ�ģ������string_en.plist�ļ�
				{
					strings = Dictionary::createWithContentsOfFile("fonts/string_en.plist"); 
					strings->retain();
					break;
				}

			case kLanguageChinese:    //ϵͳ�����ģ������string_zh.plist�ļ�
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