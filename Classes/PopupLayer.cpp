#include "PopupLayer.h"

PopupLayer::PopupLayer()
//m__pMenu(NULL)
//, m_contentPadding(0)
//, m_contentPaddingTop(0)
//, m_callbackListener(NULL)
//, m_callback(NULL)
//, m__sfBackGround(NULL)
//, m__s9BackGround(NULL)
//, m__ltContentText(NULL)
//, m__ltTitle(NULL)
//, dataTag(NULL)
{
m__pMenu=NULL;
m_contentPadding=0;
m_contentPaddingTop=0;
m_callbackListener=NULL;
m_callback=NULL;
m__sfBackGround=NULL;
m__s9BackGround=NULL;
m__ltContentText=NULL;
m__ltTitle=NULL;
dataTag=NULL;
}

PopupLayer::~PopupLayer()
{

}


PopupLayer * PopupLayer::create(const char* backgroundImage)
{
	PopupLayer* pl = PopupLayer::create();
	pl->m__sfBackGround= Sprite::create(backgroundImage);
	pl->m__s9BackGround = ui::Scale9Sprite::create(backgroundImage);
	return pl;
}


bool PopupLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}

	this->setContentSize(Size::ZERO);

	//添加按钮,设置没个按钮的位置
	Menu* menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	setMenuButton(menu);
				
	return true;
}


void PopupLayer::onEnter()
{
	Layer::onEnter();
	log("PopupLayer onEnter");

	// 弹出效果
    auto ac = Sequence::create(ScaleTo::create(0.0f, 0.0f),
                                          ScaleTo::create(0.15f, 1.05f),
                                          ScaleTo::create(0.08f, 0.95f),
                                          ScaleTo::create(0.08f, 1.0f),
										  NULL);
    this->runAction(ac);

	auto winSize = Director::getInstance()->getWinSize();

	//背景

	Size contentSize;
    // 设定好参数，在运行时加载
	if (getContentSize().equals(Size::ZERO)) 
	{				
		m__sfBackGround->setPosition(winSize.width / 2, winSize.height / 2);
        this->addChild(m__sfBackGround, 0);
        contentSize = m__sfBackGround->getTexture()->getContentSize();
    } else {
        m__s9BackGround->setContentSize(getContentSize());
        m__s9BackGround->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
        this->addChild(m__s9BackGround, 0, 0);
        contentSize = getContentSize();
    }

	//标题
	if(getLabelTitle())
	{		
		m__ltTitle->setColor(Color3B(0,0,0));
		m__ltTitle->setPosition(Vec2(winSize.width/2 ,winSize.height/2 + contentSize.height/2 - 20));
		this->addChild(m__ltTitle);
	}

	//内容
	if(getLabelContentText())
	{
		auto contentText = getLabelContentText();
		contentText->setPosition(Vec2(winSize.width/2,winSize.height/2));
		contentText->setDimensions(contentSize.width - m_contentPadding,contentSize.height - m_contentPaddingTop);
		contentText->setColor(Color3B(0,0,0));
		this->addChild(contentText);
	}	 
	

	this->addChild(getMenuButton());
	float btnWith = contentSize.width / (getMenuButton()->getChildrenCount() + 1);
	Vector<Node*> menuItems = getMenuButton()->getChildren();
	for(int i=0;i<menuItems.size();i++)
	{
		menuItems.at(i)->setPosition(Vec2(winSize.width/2 - contentSize.width/2 + btnWith*(i+1),winSize.height/2 - contentSize.height/3));
	}	


	//屏蔽下层事件响应
	auto lisenter_dialog = EventListenerTouchOneByOne::create();
	lisenter_dialog->setSwallowTouches(true);
	lisenter_dialog->onTouchBegan =[](Touch *touch ,Event *event)
	{
		log("PopupLayer touch");
		return true;
	};

	EventDispatcher *dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(lisenter_dialog,this);


}

void PopupLayer::onExit()
{
	Layer::onExit();
	log("PopupLayer onExit");	
	
}


//标题
void PopupLayer::setTitle(const char* title ,int fontsize)
{
	m__ltTitle = Label::createWithSystemFont(title,"Arial",30);
}

//内容
void PopupLayer::setContentText(const char* text ,int fontsize ,int padding ,int paddintTop)
{
	 m__ltContentText = Label::createWithSystemFont(text,"Arial",20);
	 m_contentPadding = padding;
	 m_contentPaddingTop = paddintTop;
}

//设置按钮回调函数
void PopupLayer::setCallbackFunc(Ref* target, SEL_CallFuncN callfun)
{
	m_callbackListener = target;
	m_callback = callfun;
}

//按钮回调函数
void PopupLayer::buttonCallback(Ref *pSender)
{
	auto menuItem = (MenuItem*)pSender;
	if(m_callbackListener&&m_callback)
	{
		(m_callbackListener->*m_callback)(menuItem);
	}
	//this->removeFromParent();
}

//添加按钮
bool PopupLayer::addButton(const char* normalImage, const char* selectedImage, const char* title, int tag)
{
	auto winSize = Director::getInstance()->getWinSize();

	auto menuItem = MenuItemImage::create(normalImage,selectedImage,CC_CALLBACK_1(PopupLayer::buttonCallback,this));
	menuItem->setPosition(Vec2(winSize.width/2,winSize.height/2));
	menuItem->setTag(tag);

	//给按钮图片添加文字	
	Size menuSize = menuItem->getContentSize();
	auto ttf = Label::createWithSystemFont(title,"Arial",20);
	ttf->setColor(Color3B(0,0,0));
	ttf->setPosition(Vec2(menuSize.width/2,menuSize.height/2));
	menuItem->addChild(ttf);

	getMenuButton()->addChild(menuItem);

	return true;
}