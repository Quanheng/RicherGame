#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

#include "ConstUtil.h"
#include "PopupLayer.h"
#include "MapChooseScene.h"



const int Btn_Quit_OK_TAG = 10005;
const int Btn_Quit_Cancel_TAG = 10006;
const int Quit_Dialog_Size_Width = 400;
const int Quit_Dialog_Size_Height = 220;

class MenuLayer : public cocos2d::LayerColor
{
public :
	static cocos2d::Scene *createScene();
	virtual bool init();
	virtual void onEnterTransitionDidFinish();

	CREATE_FUNC(MenuLayer);

	void startGameMenuCallback(cocos2d::Ref *pSender);
	void settingMusicMenuCallback(cocos2d::Ref *pSender);
	void quitMenuCallback(Node *pNode);
	PopupLayer* popDialog;
	void popupLayer();
	
};

#endif