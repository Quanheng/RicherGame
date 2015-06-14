#ifndef __SKILL_CARD_H__
#define __SKILL_CARD_H__

#include "cocos2d.h"
#include "Util.h"
#include "ConstUtil.h"

class SkillCard : public cocos2d::Sprite
{
public:
	//skillName�Ǽ������ƣ�strength����Ҫ������������info�Ǽ���������width�Ǽ��ܽ���Ŀ�ȣ�height�Ǽ��ܽ���߶ȣ�x��y�Ǽ��ܽ�������꣬image�Ǽ���logo
	static SkillCard *createCardSprite(cocos2d::__String *skillName,cocos2d::__String *strength,cocos2d::__String *info,int width,int height,float x,float y,int tag,char *image);
	void initCard(cocos2d::__String *skillName,cocos2d::__String *strength,cocos2d::__String *info,int width,int height,float x,float y,int tag,char *image);
	virtual bool init();
	CREATE_FUNC(SkillCard);
		
	void setStrength(int strength);
	cocos2d::LayerColor *layerColorBG;

	cocos2d::Label *labelInfo;
	cocos2d::Label *labelName;
	cocos2d::Label *labelGrade;
	cocos2d::Label *labelStrength;
	void setSkillButtonCallback(cocos2d::Ref *pSender,SEL_CallFuncN callfun);

private:
	cocos2d::__String *skillName;
	cocos2d::__String *strength;
	cocos2d::__String *info;
	//MenuItemImage *menuImage;

	void buttonCallback(cocos2d::Ref *pSender);

	//CC_SYNTHESIZE(Menu*,m_pMenu,MenuButton);

	cocos2d::Ref* m_callbackListener;
	SEL_CallFuncN m_callback;
};

#endif