#include "MenuScene.h"

USING_NS_CC;

Scene* MenuLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuLayer::create();
	scene->addChild(layer);

	return scene;
}

bool MenuLayer::init()
{
	if(!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//Ìí¼ÓLogo±³¾°
	auto logo = Sprite::create(MENU_LOGO);
	logo->setPosition(Vec2(visibleSize.width/2,visibleSize.height));
	logo->setAnchorPoint(Vec2(0.5,1));
	logo->setScale(0.6f);
	this->addChild(logo);

	//Ìí¼Ó²Êºç¾«Áé±³¾°
	auto rainbow = Sprite::create(RAINBOW);
	rainbow->setPosition(Vec2(5,visibleSize.height - 20));
	rainbow->setAnchorPoint(Vec2(0,1));
	rainbow->setScale(0.3f);
	this->addChild(rainbow);

	//ÈÃ²Êºç¾«Áé×óÓÒÒÆ¶¯
	auto ac1 = MoveBy::create(1,Vec2(8,0));
	MoveBy *ac2 = ac1->reverse();
	ActionInterval *seq =Sequence::create(ac1,ac2,NULL);
	rainbow->runAction(RepeatForever::create(seq));
	
	auto startGameMenuItem = MenuItemImage::create(NORMAL_START,PRESS_START,CC_CALLBACK_1(MenuLayer::startGameMenuCallback,this));

	auto musicOnMenuItem = MenuItemImage::create(MUSIC_ON,MUSIC_ON);
	auto musicOffMenuItem = MenuItemImage::create(MUSIC_OFF,MUSIC_OFF);
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuLayer::settingMusicMenuCallback,this),
		                                               musicOnMenuItem,
													   musicOffMenuItem,NULL);


	auto quitMenuItem = MenuItemImage::create(NORMAL_QUIT,PRESS_QUIT,CC_CALLBACK_0(MenuLayer::popupLayer,this));

	auto menu = Menu::create(startGameMenuItem,musicToggleMenuItem,quitMenuItem,NULL);

	menu->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2 - 70));
	menu->alignItemsVertically();
	this->addChild(menu);
	
	//ÉèÖÃÒôÀÖµÄ×´Ì¬£¨¿ªor¹Ø£©
	if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
	{
		musicToggleMenuItem->setSelectedIndex(0);
	}else{
		musicToggleMenuItem->setSelectedIndex(1);
	}

	return true;
}

void MenuLayer::startGameMenuCallback(Ref *pSender)
{
	if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(BUTTON_CLICK);
	}

	Director::getInstance()->pushScene(MapChooseLayer::createScene());
}

void MenuLayer::settingMusicMenuCallback(Ref *pSender)
{
	std::vector<char*> bgMusicVector;
	bgMusicVector.push_back(BG01_MP3);
	bgMusicVector.push_back(BG02_MP3);
	bgMusicVector.push_back(BG03_MP3);

	auto defaults = UserDefault::getInstance();
	if(defaults->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		defaults->setBoolForKey(MUSIC_KEY,false);
	}
	else
	{
		defaults->setBoolForKey(MUSIC_KEY,true);
		SimpleAudioEngine::getInstance()->playEffect(BUTTON_CLICK);

		//²¥·ÅÒôÀÖ´úÂë
		//struct timeval now; 
		//gettimeofday(&now, NULL);
		//unsigned rand_seed = (unsigned)(now.tv_sec*1000 + now.tv_usec/1000);    //¶¼×ª»¯ÎªºÁÃë 
		//srand(rand_seed);
		int rand1 = rand()%(bgMusicVector.size());
		//SimpleAudioEngine::getInstance()->playBackgroundMusic(bgMusicVector.at(rand1));
	}

}

void MenuLayer::quitMenuCallback(Node *pNode)
{
	if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(BUTTON_CLICK);
	}

	if(pNode->getTag() == Btn_Quit_OK_TAG)
	{
		Director::getInstance()->end();
	}else
	{
		popDialog->removeFromParent();
		return;
	}	
	
}

void MenuLayer::popupLayer()
{
	if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(BUTTON_CLICK);
	}

	popDialog = PopupLayer::create(DIALOG_BG);
	popDialog->setContentSize(Size(Quit_Dialog_Size_Width,Quit_Dialog_Size_Height));
	popDialog->setTitle(LanguageString::getInstance()->getLanguageString(DIALOG_TITLE)->getCString());
	popDialog->setContentText(LanguageString::getInstance()->getLanguageString(DIALOG_CONTENT)->getCString(),20,60,250);
	popDialog->setCallbackFunc(this,callfuncN_selector(MenuLayer::quitMenuCallback));
	popDialog->addButton(BUTTON_BG1,BUTTON_BG3,LanguageString::getInstance()->getLanguageString(OK)->getCString(),Btn_Quit_OK_TAG);
	popDialog->addButton(BUTTON_BG1,BUTTON_BG3,LanguageString::getInstance()->getLanguageString(CANCEL)->getCString(),Btn_Quit_Cancel_TAG);
	this->addChild(popDialog);
	
}

void MenuLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("MenuLayer onEnterTransitionDidFinish ");

	if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
	{
		//SimpleAudioEngine::getInstance()->playBackgroundMusic(BG01_MP3);
	}
	
}
