#include "SkillCard.h"

bool SkillCard::init()
{
	if(!Sprite::init())
	{
		return false;
	}
	return true;
}

SkillCard* SkillCard::createCardSprite(__String *skillName,__String *strength,__String *info,int width,int height,float x,float y,int tag,char *image)
{
	SkillCard *skillCard = new SkillCard;
	if(skillCard&&skillCard->init())     //如果创建并初始化成功
	{
		skillCard->autorelease();
		skillCard->initCard(skillName,strength,info,width,height,x,y,tag,image);
		return skillCard;
	}
	CC_SAFE_DELETE(skillCard);
	return nullptr;
}

void SkillCard::initCard(__String *skillName,__String *strength,__String *info,int width,int height,float x,float y,int tag,char *image)
{
	this->skillName = skillName;
	this->info = info;
	this->strength =strength;

	layerColorBG = LayerColor::create(Color4B(100,120,90,255),width,height);
	layerColorBG->setPosition(Vec2(x,y));

	//技能logo
	Sprite *skillIamge = Sprite::create(image);
	skillIamge->setPosition(Vec2(0,layerColorBG->getContentSize().height));
	layerColorBG->addChild(skillIamge);

	//技能名称
	labelName = Label::createWithSystemFont(skillName->getCString(),"Arial",15);
	labelName->setColor(Color3B(200,200,200));
	labelName->setPosition(Vec2(layerColorBG->getContentSize().width/2 - labelName->getContentSize().width/2, layerColorBG->getContentSize().height - 5));
	labelName->setAnchorPoint(Vec2(0,1));
	layerColorBG->addChild(labelName);

	//技能消耗
	labelStrength = Label::createWithSystemFont(strength->getCString(),"Arial",15);
	labelStrength->setColor(Color3B(200,200,200));
    labelStrength->setPosition(Vec2(5,layerColorBG->getContentSize().height/2-10));
	labelStrength->setAnchorPoint(Vec2(0,0));
	layerColorBG->addChild(labelStrength);

	if(info != NULL)
    {
		//技能描述
		labelInfo = Label::createWithSystemFont(info->getCString(),"Arial",15);
		labelInfo->setColor(Color3B(200,200,200));
        labelInfo->setPosition(Vec2(5,layerColorBG->getContentSize().height/2-40));
		labelInfo->setAnchorPoint(Vec2(0,0));
		layerColorBG->addChild(labelInfo);
    }

	auto menuItem = MenuItemImage::create("images/check_normal.png", "images/check_pressed.png",CC_CALLBACK_1(SkillCard::buttonCallback,this));
	menuItem->setPosition(Vec2(layerColorBG->getContentSize().width - menuItem->getContentSize().width ,layerColorBG->getContentSize().height/2));
	menuItem->setTag(tag);

	Menu *menu = Menu::create(menuItem,NULL);
	menu->setPosition(Vec2::ZERO);
	layerColorBG->addChild(menu);

	this->addChild(layerColorBG);
}

void SkillCard::buttonCallback(Ref *pSender)
{
	auto menuItem = (MenuItem*)pSender;
	if(m_callbackListener&&m_callback)
	{
		(m_callbackListener->*m_callback)(menuItem);
	}
}

void SkillCard::setSkillButtonCallback(Ref *target,SEL_CallFuncN callfun)
{
    m_callbackListener = target;
    m_callback = callfun;    
}

void SkillCard::setStrength(int strength)
{
	labelStrength->setString(__String::createWithFormat("%s:%d", LanguageString::getInstance()->getLanguageString(LOST_STRENGTH)->getCString(),strength)->getCString());
}