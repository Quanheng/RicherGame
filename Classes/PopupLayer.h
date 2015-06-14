#ifndef __POPUP_LAYER_H__
#define __POPUP_LAYER_H__

#include "cocos2d.h"
#include "ConstUtil.h"
#include "ui\UIScale9Sprite.h"


USING_NS_CC;

typedef enum{
	okMenuTag = 101,
	cencelMenuTag
}ButtonType;

const int Pop_FontSize = 20;   


class PopupLayer : public cocos2d::Layer
{
public:	
	PopupLayer();
	~PopupLayer();

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	static PopupLayer * create(const char* backgroundImage);
	void setTitle(const char* title ,int fontsize=Pop_FontSize);
	void setContentText(const char* text ,int fontsize=Pop_FontSize ,int padding=50 ,int paddintTop=100);
	void setCallbackFunc(cocos2d::Ref* target, SEL_CallFuncN callfun);
	
	bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag=0);

	CREATE_FUNC(PopupLayer);	

private:
	void buttonCallback(cocos2d::Ref* pSender);

	cocos2d::Ref* m_callbackListener;
    SEL_CallFuncN m_callback;

    // 文字内容两边的空白区
    int m_contentPadding;
    int m_contentPaddingTop; 
	CC_SYNTHESIZE(Menu*, m__pMenu, MenuButton);
    CC_SYNTHESIZE(Sprite*, m__sfBackGround, SpriteBackGround);
    CC_SYNTHESIZE(ui::Scale9Sprite*, m__s9BackGround, Sprite9BackGround);
    CC_SYNTHESIZE(Label*, m__ltTitle, LabelTitle);
    CC_SYNTHESIZE(Label*, m__ltContentText, LabelContentText);

	CC_SYNTHESIZE(int, dataTag, DataTag);    //标示，代表消息类型
		
};

#endif