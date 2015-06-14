#ifndef __MAP_CHOOSE_SCENE_H__
#define __MAP_CHOOSE_SCENE_H__

#include "cocos2d.h"
#include "ConstUtil.h"
#include "MenuScene.h"
#include "SeaScene.h"
#include "BeachScene.h"
#include "SnowScene.h"

USING_NS_CC;

#define BEACH_MAP_TAG    201
#define SEA_MAP_TAG      202
#define SNOW_MAP_TAG     203

#define LEFT_MENU_TAG    301
#define RIGHT_MENU_TAG   302

class MapChooseLayer : public cocos2d::Layer 
{
public:
	static cocos2d::Scene *createScene();
	virtual bool init();
	virtual void onEnter();
	CREATE_FUNC(MapChooseLayer);	
	
private:
	//创建3张图片精灵
	cocos2d::Sprite *beachMap;
	cocos2d::Sprite *seaMap;
	cocos2d::Sprite *snowMap;

	//创建左右menu
	cocos2d::MenuItemImage *leftMenuItem;
	cocos2d::MenuItemImage *rightMenuItem;

	int currentPage;      //当前是第几张关卡地图
	Size mapSize;         //地图的尺寸
	int len;              //地图移动的距离

	void backCallback(cocos2d::Ref *pSender);
	void buttonLeftCallback(cocos2d::Ref *pSender);
	void buttonRightCallback(cocos2d::Ref *pSender);
	void buttonStartCallback(cocos2d::Ref *pSender);
};

#endif