#ifndef __UTIL_H__
#define __UTIL_H__

#include "cocos2d.h"
#include "LanguageString.h"

#define winSize Director::getInstance()->getWinSize()


USING_NS_CC;

struct Util
{
	static Point map2GL(const Vec2& ptMap, TMXTiledMap* map)
	{
		Vec2 ptUI;
		ptUI.x = ptMap.x * map->getTileSize().width;
		ptUI.y = (ptMap.y + 1)* map->getTileSize().height;

		Vec2 ptGL = ptUI;
		ptGL.y = map->getContentSize().height - ptUI.y;
		return ptGL;
	}
	static Point GL2map(const Vec2& ptGL, TMXTiledMap* map)
	{
		Vec2 ptUI = ptGL;
		ptUI.y = map->getContentSize().height - ptGL.y;

		int x = ptUI.x / map->getTileSize().width;
		int y = ptUI.y / map->getTileSize().height;
		return Vec2(x, y);
	}
	
	static Vector<__String*> splitString(const char* srcStr, const char* sSep)
	{
		Vector<__String*> stringList ;  
  
		int size = strlen(srcStr);  
		__String* str = String::create(srcStr);  
  
		int startIndex = 0;  
		int endIndex = 0;  
		endIndex = str->_string.find(sSep);  
  
		__String* spliStr = NULL;  
  
		while(endIndex > 0) {  
			spliStr = __String::create("");  
 			/* 截取字符串 */  
			spliStr->_string = str->_string.substr(startIndex, endIndex);  
  			/* 添加字符串到列表 */  
			stringList.pushBack(spliStr);  
  			/* 截取剩下的字符串 */  
			str->_string = str->_string.substr(endIndex + 1, size);  
			/* 查找下一个分隔符所在下标 */  
			endIndex = str->_string.find(sSep);  
		}  
		/* 剩下的字符串也添加进列表 */  
		if(str->_string.compare("") != 0) {  
			stringList.pushBack(__String::create(str->_string));  
		}  
  
		return stringList; 
		

	}

};


#endif