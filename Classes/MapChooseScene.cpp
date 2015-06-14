#include "MapChooseScene.h"

Scene* MapChooseLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = MapChooseLayer::create();
	scene->addChild(layer);

	return scene;
}

bool MapChooseLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create(STAGE_BACKGROUND);
	bg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	this->addChild(bg);

	return true;
}

void MapChooseLayer::onEnter()
{
	Layer::onEnter();
	log("MapChooseLayer onEnter");

	auto visibleSize = Director::getInstance()->getVisibleSize();

	
	
	//��ʼ�����ŵ�ͼ����
	beachMap = Sprite::create(BEACH_ITEM);
	seaMap = Sprite::create(SEA_ITEM);
	snowMap = Sprite::create(SNOW_ITEM);

	mapSize = beachMap->getContentSize();           //��ȡ��ͼ�����С

	beachMap->setPosition(Vec2(-mapSize.width/2, visibleSize.height/2));
	beachMap->setTag(BEACH_MAP_TAG);
	this->addChild(beachMap);

	
	seaMap->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	seaMap->setTag(SEA_MAP_TAG);
	this->addChild(seaMap);

	
	snowMap->setPosition(Vec2(visibleSize.width + mapSize.width/2, visibleSize.height/2));
	snowMap->setTag(SNOW_MAP_TAG);
	this->addChild(snowMap);

	//���ذ�ť
	auto backMenuItem = MenuItemImage::create(BACK_NORMAL,BACK_SELECTED,CC_CALLBACK_1(MapChooseLayer::backCallback,this));
	backMenuItem->setPosition(Vec2(backMenuItem->getContentSize().width/2 +20,visibleSize.height -backMenuItem->getContentSize().height/2 - 20));
	//backMenuItem->setScale(0.5);
	backMenuItem->setAnchorPoint(Vec2(0.5,0.5));

	//��ʼ����߰�ť
	leftMenuItem = MenuItemImage::create(BUTTON_NORMAL,BUTTON_SELECTED,BUTTON_DISABLE,
											CC_CALLBACK_1(MapChooseLayer::buttonLeftCallback,this));
	leftMenuItem->setPosition(Vec2(visibleSize.width/2 - mapSize.width/2 -50 ,visibleSize.height/2));
	leftMenuItem->setTag(LEFT_MENU_TAG);

	//��ʼ���ұ߰�ť
	rightMenuItem = MenuItemImage::create(BUTTON_NORMAL,BUTTON_SELECTED,BUTTON_DISABLE,
											CC_CALLBACK_1(MapChooseLayer::buttonRightCallback,this));
	rightMenuItem->setRotation(180);   //��ת180��
	rightMenuItem->setPosition(Vec2(visibleSize.width/2 + mapSize.width/2 +50 ,visibleSize.height/2));
	rightMenuItem->setTag(RIGHT_MENU_TAG);

	//������ʼ��Ϸ��ť
	auto startGameMenuItem = MenuItemImage::create(BUTTON_ENTER_NORMAL,BUTTON_ENTER_SELECTED,
												CC_CALLBACK_1(MapChooseLayer::buttonStartCallback,this));
	startGameMenuItem->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 - mapSize.height/2 - 25));
	startGameMenuItem->setScale(0.5f);

	auto menu = Menu::create(backMenuItem,leftMenuItem,rightMenuItem,startGameMenuItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,1);

	currentPage =2;
	len = visibleSize.width/2 +mapSize.width/2;
}

void MapChooseLayer::backCallback(Ref *pSender)
{
	if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(BUTTON_CLICK);
	}

	Director::getInstance()->popScene();
}

void MapChooseLayer::buttonLeftCallback(Ref *pSender)
{		
	if(currentPage>1)
	{
		if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
		{
			SimpleAudioEngine::getInstance()->playEffect(BUTTON_CLICK);
		}

		beachMap->runAction(MoveBy::create(0.5,Vec2(len,0)));
		seaMap->runAction(MoveBy::create(0.5,Vec2(len,0)));
		snowMap->runAction(MoveBy::create(0.5,Vec2(len,0)));

		currentPage -= 1;
		rightMenuItem->setEnabled(true);

		if(currentPage==1)
		{
			//�����ǰ�ǵ�һ�ŵ�ͼ������ť������
			leftMenuItem->setEnabled(false);			
		}
	}
}

void MapChooseLayer::buttonRightCallback(Ref *pSender)
{
	if(currentPage<3)
	{
		if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
		{
			SimpleAudioEngine::getInstance()->playEffect(BUTTON_CLICK);
		}

		beachMap->runAction(MoveBy::create(0.5,Vec2(-len,0)));
		seaMap->runAction(MoveBy::create(0.5,Vec2(-len,0)));
		snowMap->runAction(MoveBy::create(0.5,Vec2(-len,0)));

		currentPage += 1;
		leftMenuItem->setEnabled(true);

		if(currentPage==3)
		{
			//�����ǰ�ǵ����ŵ�ͼ�����Ұ�ť������
			rightMenuItem->setEnabled(false);		
			
		}
	}
}

void MapChooseLayer::buttonStartCallback(Ref *pSender)
{
	if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(BUTTON_CLICK);
	}
	if(currentPage==1)
	{
		auto scene =BeachLayer::createScene();
		auto sc = TransitionFadeBL::create(2,scene);
		Director::getInstance()->pushScene(sc);
	}

	if(currentPage==2)
	{
		auto scene =SeaLayer::createScene();
		auto sc = TransitionFadeBL::create(2,scene);
		Director::getInstance()->pushScene(sc);
	}
	if(currentPage==3)
	{
		auto scene =SnowLayer::createScene();
		auto sc = TransitionFadeBL::create(2,scene);
		Director::getInstance()->pushScene(sc);
	}
}