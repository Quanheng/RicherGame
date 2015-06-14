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
	//����3��ͼƬ����
	cocos2d::Sprite *beachMap;
	cocos2d::Sprite *seaMap;
	cocos2d::Sprite *snowMap;

	//��������menu
	cocos2d::MenuItemImage *leftMenuItem;
	cocos2d::MenuItemImage *rightMenuItem;

	int currentPage;      //��ǰ�ǵڼ��Źؿ���ͼ
	Size mapSize;         //��ͼ�ĳߴ�
	int len;              //��ͼ�ƶ��ľ���

	void backCallback(cocos2d::Ref *pSender);
	void buttonLeftCallback(cocos2d::Ref *pSender);
	void buttonRightCallback(cocos2d::Ref *pSender);
	void buttonStartCallback(cocos2d::Ref *pSender);
};

#endif