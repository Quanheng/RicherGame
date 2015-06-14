#include "GameBaseScene.h"

USING_NS_CC;
     //static �����������ʼ��
     int GameBaseLayer::tiledColsCount;
	 int GameBaseLayer::tiledRowsCount;
	 bool** GameBaseLayer::canPassGrid;
	 Vector<RicherPlayer*>  GameBaseLayer::players_vector;
	 Vector<Sprite*> GameBaseLayer::pathMarkVector;

	 TMXLayer* GameBaseLayer::landLayer;
	  TMXLayer* GameBaseLayer::wayLayer;
	 TMXTiledMap* GameBaseLayer::_map;

	 int  GameBaseLayer::blank_land_tiledID;
	 int  GameBaseLayer::strength_30_tiledID;
	 int  GameBaseLayer::strength_50_tiledID;
	 int  GameBaseLayer::strength_80_tiledID;

	 int  GameBaseLayer::randomEvent_tiledID;
	 int  GameBaseLayer::lottery_tiledID;
	 int  GameBaseLayer::stock_tiledID;

	 int GameBaseLayer::player1_building_1_tiledID;
	 int GameBaseLayer::player1_building_2_tiledID;
	 int GameBaseLayer::player1_building_3_tiledID;

	 int GameBaseLayer::player2_building_1_tiledID;
	 int GameBaseLayer::player2_building_2_tiledID;
	 int GameBaseLayer::player2_building_3_tiledID;
	  
bool GameBaseLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	//addMap();                //��ӵ�ͼ
	addRightBanner();	     //����ұߵı��
	drawTable(2);	         //�����
	addDigiteRoundSprite();  //������־���
	refresshRoundDisplay();  //���»غϼ���
	addGoButton();           //���Go��ť
	//initTiledGrid();         //��ʼ����ͼ��ά���飬����ÿ���ؿ��ĵ�ͼ��С��һ�����������������������ʵ��
	setWayPassToGrid();      //����ͼ��way������canPassGrid������Ӧ��ֵΪtrue
	addPathMark();           //���·�����
	addPlayer();             //��ӽ�ɫ
	addDice();               //�������
	addNotificationObserver();  //�����Ϣ������
	gameRoundCount = 0 ;     //��ʼ���غ���
	initLandLayerFromMap();  //��ʼ��land��
	
	//initPropTiledID();       //��ʼ������ID,����ÿ���ؿ��ĵ�ͼ��С��һ�����������������������ʵ��

	particleForBuyLand();    //���ؽ�ӡ����Ķ���
	initRandomAskEventMap(); //��ʼ��Map����������ʺ�����¼�
	addPlayerStrengthUpAniate();  //������������Ķ���

	initAudioEffect();    //�����Ч��������
	return true;
}
void GameBaseLayer::onEnter()
{
	Layer::onEnter();
	log("GameBaseLayer onEnter");

	
}

void GameBaseLayer::onExit()
{
	Layer::onExit();
	log("GameBaseLayer onExit");

	for(int i=0; i < tiledRowsCount; i++)
	{
		CC_SAFE_DELETE(canPassGrid[i]);
	}
	CC_SAFE_DELETE(canPassGrid);

	diceAnimate->release();
	scaleBy1ForBuyLand->release();
	scaleBy2ForBuyLand->release();
	landFadeIn->release();
	landFadeOut->release();
	strengthUpAnimate->release();

	players_vector.clear();
	pathMarkVector.clear();
}

void GameBaseLayer::addRightBanner()
{
	auto rightBanner = Sprite::create(RIGHT_BANNER);
	rightBanner->setPosition(Vec2(tableStartPosition_x,0));
	rightBanner->setAnchorPoint(Vec2(0,0));
	this->addChild(rightBanner);
}

void GameBaseLayer::drawTable(int playerNumber)
{
	auto size = Director::getInstance()->getVisibleSize();

	auto draw = DrawNode::create();
	this->addChild(draw);

	for(int i=0;i<playerNumber;i++)  
    {  
        draw->drawSegment(Vec2(tableStartPosition_x,tableStartPosition_y-2*i*tableHeight),   
                          Vec2(tableStartPosition_x+ 3*tableWidth,tableStartPosition_y-2*i*tableHeight), 1,   
                          Color4F(0, 1, 0, 1));  
   
        draw->drawSegment(Vec2(tableStartPosition_x,tableStartPosition_y - 2*(i+1)*tableHeight),   
                          Vec2(tableStartPosition_x+ 3*tableWidth,tableStartPosition_y - 2*(i+1)*tableHeight), 1,   
                          Color4F(0, 1, 0, 1));  
   
        draw->drawSegment(Vec2(tableStartPosition_x+ tableWidth,tableStartPosition_y - tableHeight-2*i*tableHeight),   
                          Vec2(tableStartPosition_x+ 3*tableWidth,tableStartPosition_y - tableHeight-2*i*tableHeight), 1,   
                          Color4F(0, 1, 0, 1));  
   
        draw->drawSegment(Vec2(tableStartPosition_x+ tableWidth,tableStartPosition_y -2*i*tableHeight),   
                          Vec2(tableStartPosition_x+ tableWidth,tableStartPosition_y -2* tableHeight-2*i*tableHeight), 1,   
                          Color4F(0, 1, 0, 1));  
    } 
}

void GameBaseLayer::addPlayerInfo()
{
		//////////�����start//////////
	Sprite* player1_logo = Sprite::create(PLAYER_ME);  
    player1_logo->setPosition(tableStartPosition_x+tableWidth/2,tableStartPosition_y-tableHeight);  
    this->addChild(player1_logo);  
   
    player1_money_label = Label::createWithTTF("$","fonts/arial.ttf",25);   
    player1_money_label->setAnchorPoint(Vec2(0,0.5));  
    player1_money_label->setPosition(tableStartPosition_x+tableWidth,tableStartPosition_y-tableHeight/2);  
    addChild(player1_money_label);  
   
	player1_strength_label = Label::createWithTTF("+","fonts/arial.ttf",28);	
	player1_strength_label->setAnchorPoint(Vec2(0,0.5));
    player1_strength_label->setPosition(tableStartPosition_x+tableWidth,tableStartPosition_y-tableHeight/2*3);  
    addChild(player1_strength_label);  
   
    Sprite* player2_logo = Sprite::create(PLAYER_ENEMY1);  
    player2_logo->setPosition(tableStartPosition_x+tableWidth/2,tableStartPosition_y-3*tableHeight);  
    addChild(player2_logo);  
   
	player2_money_label = Label::createWithTTF("$","fonts/arial.ttf",25);	
    player2_money_label->setAnchorPoint(Vec2(0,0.5));  
    player2_money_label->setPosition(tableStartPosition_x+tableWidth,tableStartPosition_y-tableHeight/2*5);  
    addChild(player2_money_label);  
   
	player2_strength_label = Label::createWithTTF("+","fonts/arial.ttf",28);	
    player2_strength_label->setAnchorPoint(Vec2(0,0.5));  
    player2_strength_label->setPosition(tableStartPosition_x+tableWidth,tableStartPosition_y-tableHeight/2*7);  
    addChild(player2_strength_label);  
	//////////�����end//////////
}

void GameBaseLayer::addPlayer()
{
	addPlayerInfo();

	/////////��ӽ�ɫ����ͼ�����λ��////////////

	//ָ����������ӣ����������������Ӳ��� ���õ�ǰʱ������������ӣ�
	struct timeval now;
	gettimeofday(&now,NULL);//����ʱ������
	unsigned rand_seed =(unsigned)(now.tv_sec*1000 + now.tv_usec/1000);// ��ʼ�������   
	srand(rand_seed);

	//��ɫ1
	player1 = RicherPlayer::create(PLAYER_1_NAME,PLAYER_1_TAG,false);	
	int _rand1 =rand()%(wayLayerPass_Vector.size());       //��ȡһ��0~��������֮��������
	Vec2 vec2ForPlayer1 = wayLayerPass_Vector.at(_rand1);
	//������Ǹ�����λ�����һ��tiledHeight�߶ȣ�Ŀ����Ϊ���ý�ɫ������ʾ�ڵ�·��
    vec2ForPlayer1.y +=tiledHeight; 
	player1->setPosition(vec2ForPlayer1);
	player1->setAnchorPoint(Vec2(0,0.5));

	char money1[20];
	memset(money1,0,20);
	sprintf(money1,"$%d",player1->getMoney());
	player1_money_label->setString(money1);                   //��ʾ��ɫ��Ǯ

	char strength1[20];
	memset(strength1,0,20);
	sprintf(strength1,"+%d",player1->getStrength());
	player1_strength_label->setString(strength1);                //��ʾ��ɫ����

	this->addChild(player1);
	players_vector.pushBack(player1);

	//��ɫ2
	player2 = RicherPlayer::create(PLAYER_2_NAME,PLAYER_2_TAG,true);
	int _rand2 =rand()%(wayLayerPass_Vector.size());       //��ȡһ��0~��������֮��������
	Vec2 vec2ForPlayer2 = wayLayerPass_Vector.at(_rand2);
	//������Ǹ�����λ�����һ��tiledHeight�߶ȣ�Ŀ����Ϊ���ý�ɫ������ʾ�ڵ�·��
    vec2ForPlayer2.y +=tiledHeight; 
	player2->setPosition(vec2ForPlayer2);
	player2->setAnchorPoint(Vec2(0,0.5));

	char money2[20];
	memset(money2,0,20);
	sprintf(money2,"$%d",player2->getMoney());
	player2_money_label->setString(money2);                   //��ʾ��ɫ��Ǯ

	char strength2[20];
	memset(strength2,0,20);
	sprintf(strength2,"+%d",player2->getStrength());
	player2_strength_label->setString(strength2);                //��ʾ��ɫ����

	this->addChild(player2);
	players_vector.pushBack(player2);
}

void GameBaseLayer::addGoButton()
{
	//GO��ť
	goMenuItem = MenuItemImage::create(GO_BUTTON_NORMAL,GO_BUTTON_SELECTED,CC_CALLBACK_1(GameBaseLayer::goButtomCallback,this));
	goMenuItem->setPosition(Vec2(tableStartPosition_x + 1.5*tableWidth,tableStartPosition_y - tableHeight * 6.5));
	goMenuItem->setScale(0.8);
	goMenuItem->setTag(GO_MENU_ITEM_TAG);
	goMenuItem->setAnchorPoint(Vec2(0.5,0.5));

	//���ܰ�ť
	skillMenuItem = MenuItemImage::create("images/skill_button_normal.png","images/skill_button_pressed.png",CC_CALLBACK_1(GameBaseLayer::goButtomCallback,this));
	skillMenuItem->setPosition(Vec2(tableStartPosition_x + 1.5*tableWidth,tableStartPosition_y - tableHeight * 7 - goMenuItem->getContentSize().height/2 ));
	skillMenuItem->setScale(0.8);
	skillMenuItem->setTag(SKILL_MENU_ITEM_TAG);
	skillMenuItem->setAnchorPoint(Vec2(0.5,0.5));

	menu = Menu::create(goMenuItem,skillMenuItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,1,MENU_TAG);
	
	//�������꼼����ʾ���� 
	skillStorm = SkillCard::createCardSprite(
		LanguageString::getInstance()->getLanguageString(RAIN),
		LanguageString::getInstance()->getLanguageString(LOST_STRENGTH),
		LanguageString::getInstance()->getLanguageString(DOWN_GRADE),
		skillSpriteCardWidth,
		skillSpriteCardHeight,
		150,
		-130,
		skillStormTag,
		"images/thunderstorm.png"
		);
	this->addChild(skillStorm,50);
	
	//��ȡ������ʾ����  
	skillTransfer = SkillCard::createCardSprite(
		LanguageString::getInstance()->getLanguageString(YOURS_IS_MINE),
		LanguageString::getInstance()->getLanguageString(LOST_STRENGTH),
		LanguageString::getInstance()->getLanguageString(YOURS_IS_MINE_INFO),
		skillSpriteCardWidth,
		skillSpriteCardHeight,
		410,
		-130,
		skillTransferTag,
		"images/skill_transfer.png"
		);
	this->addChild(skillTransfer,50);

	//��Ӹ������ܽ������ص�����  
	skillStorm->setSkillButtonCallback(this,callfuncN_selector(GameBaseLayer::skillStormCallback));
	skillTransfer->setSkillButtonCallback(this,callfuncN_selector(GameBaseLayer::skillTransferCallback));

	//���ܽ����Ƿ�����ʾ  
	isShowSkillLayer = false;
	
}




void GameBaseLayer::setWayPassToGrid()
{
	wayLayer = _map->getLayer("way");   //��ȡ��ͼway��
	Size _mapSize = wayLayer->getLayerSize();
	//����wayͼ�㣬��ȡ��·�����꣬��ת��������ֵ����canPassGrid���Ӧ��λ������true������¼����ͨ���ĵ�·
	for(int i=0;i<_mapSize.width;i++)
	{
		for(int j=0;j<_mapSize.height;j++)
		{
			auto _sp = wayLayer->getTileAt(Point(i,j));
			if(_sp)
			{
				int row = _sp->getPositionY()/tiledWidth;
				int col = _sp->getPositionX()/tiledHeight;
				canPassGrid[row][col] =true;
				Vec2 p = _sp->getPosition();
				wayLayerPass_Vector.push_back(p);   //�����걣�浽������  
				log("canPassGrid row=  %d ,col =%d ,canpass = %d" ,row,col,canPassGrid[row][col]);
			}

		}
	}
	log("setWayPassToGrid finished");

}


void GameBaseLayer::goButtomCallback(Ref *pSender)
{	
	//��Ч
	if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(BUTTON_CLICK_01);
	}

	auto menuItem = (MenuItem*)pSender;
	if(menuItem->getTag()==GO_MENU_ITEM_TAG)
	{
		randNumber= rand()%6 + 1;
		RouteNavigation::getInstance()->getPath(player1,randNumber,canPassGrid,tiledRowsCount,tiledColsCount);
		std::vector<int> rowVector = RouteNavigation::getInstance()->getPathRows_vector();
		std::vector<int> colVector = RouteNavigation::getInstance()->getPathCols_vector();
	
		for(int i=0;i<rowVector.size();i++)
		{
			log(" rowVector row is %d --- colVector col is %d",rowVector[i],colVector[i]);
		}

		NotificationCenter::getInstance()->postNotification(MSG_GO,String::create("0"));
		player1->startGo(rowVector,colVector);	

		
		if(isShowSkillLayer)
		{
			showSkillSprites();   //���ؼ��ܽ��溯��
		}		
	}
	else if(menuItem->getTag() == SKILL_MENU_ITEM_TAG)
	{
		//�������ĵ�����
		skillStorm->setStrength(50);
		skillTransfer->setStrength(100);
				
		showSkillSprites();   //��ʾ/���ؼ��ܽ���
	}
	
}

void GameBaseLayer::showSkillSprites()     //��ʾ/���ؼ��ܽ��溯��
{
	if(!isShowSkillLayer)
	{
		skillStorm->runAction(MoveBy::create(0.3,Vec2(0,130)));  
        skillTransfer->runAction(MoveBy::create(0.3,Vec2(0,130)));  
        isShowSkillLayer = true;  
	}
	else
	{
		skillStorm->runAction(MoveBy::create(0.3,Vec2(0,-130)));  
        skillTransfer->runAction(MoveBy::create(0.3,Vec2(0,-130)));  
        isShowSkillLayer = false;  
	}
}

void GameBaseLayer::skillStormCallback(Node* node)
{
	if(player1->getStop_x()<0)    //�ж�ͣ��λ���Ƿ��ǳ�ʼ״̬
	{
		return;
	}
	if(player1->getStrength()>=50)   //�жϵ�ǰ�����Ƿ���ڵ��ڼ�����������
	{
		int landTag = landLayer->getTileGIDAt(Vec2(player1->getStop_x(),player1->getStop_y()));
		if(landTag != player1_building_1_tiledID && landTag != player1_building_2_tiledID && landTag != player1_building_3_tiledID)
		{
			//��Ч
			if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
			{
				SimpleAudioEngine::getInstance()->playEffect(STORM_EFFECT);
				int rand1 = rand()%(player1EffectVec_4.size());
				SimpleAudioEngine::getInstance()->playEffect(player1EffectVec_4.at(rand1)->getCString());
				nextPlayerEffectVec = player2EffectVec_5;
				this->scheduleOnce(schedule_selector(GameBaseLayer::playNextEffectVec),2.0f);
			}
			goMenuItem->setEnabled(false);   //�����ͷŹ����У����������ߣ���Ӱ�켼���жϵ�ǰλ��

			showSkillSprites();  //���ؽ��� 
			refreshStrength(player1,-50);             //�۳����ĵ�����
			Vec2 pointOfGL = Util::map2GL(Vec2(player1->getStop_x(),player1->getStop_y()),GameBaseLayer::_map);   

			auto rainSprite = Sprite::createWithSpriteFrame(player1->getRain_skill_animate()->getAnimation()->getFrames().at(0)->getSpriteFrame());					
			rainSprite->setAnchorPoint(Vec2(0,0));
			rainSprite->setPosition(pointOfGL + Vec2(-tiledWidth/2,tiledHeight/2));
			this->addChild(rainSprite);

			rainSprite->runAction(Sequence::create(
				player1->getRain_skill_animate(),              //���Ŷ���
				CallFunc::create([this,rainSprite]()
				{
					landLayer->setTileGID(blank_land_tiledID,Vec2(player1->getStop_x(),player1->getStop_y()));  //�����ر�ɿյ�
					rainSprite->removeFromParent();   //�Ƴ�
					goMenuItem->setEnabled(true);   //�����ͷ���ϣ��������� 
				}),
				NULL));		
		}		
	}
	else   //����������㣬����ʾ
	{
		CocosToast::createToast(
			this,
			LanguageString::getInstance()->getLanguageString(YOUR_STRENGTH_IS_LOW)->getCString(),
			TOAST_SHOW_TIME,
			winSize/2);
	}
}


void GameBaseLayer::skillTransferCallback(Node* node)
{
	if(player1->getStop_x()<0)    //�ж�ͣ��λ���Ƿ��ǳ�ʼ״̬
	{
		return;
	}	
	
	if(player1->getStrength()>=100)   //�жϵ�ǰ�����Ƿ���ڵ��ڼ�����������
	{
		//��ȡ���ص�tiledID
		int transferLand = 0;
		if(transferLandTag== MSG_PAY_TOLLS_1_TAG)
		{
			transferLand = player1_building_1_tiledID;
		}
		if(transferLandTag== MSG_PAY_TOLLS_2_TAG)
		{
			transferLand = player1_building_2_tiledID;
		}
		if(transferLandTag== MSG_PAY_TOLLS_3_TAG)
		{
			transferLand = player1_building_3_tiledID;
		}
		transferLandTag = 0;

		if(transferLand !=0)
		{
			//��Ч
			if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
			{
				int rand1 = rand()%(player1EffectVec_2.size());
				SimpleAudioEngine::getInstance()->playEffect(player1EffectVec_2.at(rand1)->getCString());
				nextPlayerEffectVec = player2EffectVec_3;
				this->scheduleOnce(schedule_selector(GameBaseLayer::playNextEffectVec),2.0f);
			}
			goMenuItem->setEnabled(false);   //�����ͷŹ����У����������ߣ���Ӱ�켼���жϵ�ǰλ��

			showSkillSprites();  //���ؽ��� 
			refreshStrength(player1,-100);             //�۳����ĵ�����
			Vec2 pointOfGL = Util::map2GL(Vec2(player1->getStop_x(),player1->getStop_y()),GameBaseLayer::_map);   

			auto transferSprite = Sprite::createWithSpriteFrame(player1->getTransfer_skill_animate()->getAnimation()->getFrames().at(0)->getSpriteFrame());					
			transferSprite->setAnchorPoint(Vec2(0,0));
			transferSprite->setPosition(pointOfGL);
			this->addChild(transferSprite);

			transferSprite->runAction(Sequence::create(
				player1->getTransfer_skill_animate(),              //���Ŷ���
				CallFunc::create([this,transferSprite,transferLand]()
				{
					landLayer->setTileGID(transferLand,Vec2(player1->getStop_x(),player1->getStop_y()));  //�����ر���Լ���
					transferSprite->removeFromParent();   //�Ƴ�
					goMenuItem->setEnabled(true);   //�����ͷ���ϣ��������� 
				}),
				NULL));			
		}		
	}
	else   //����������㣬����ʾ
	{
		CocosToast::createToast(
			this,
			LanguageString::getInstance()->getLanguageString(YOUR_STRENGTH_IS_LOW)->getCString(),
			TOAST_SHOW_TIME,
			winSize/2);
	}
}


void GameBaseLayer::addNotificationObserver()
{
	//����MSG_GO��Ϣ����go������/����
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseLayer::receiveNotificationOMsg),
		MSG_GO,
		NULL);

	//����MSG_BUY��Ϣ�������������¼�
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseLayer::receiveNotificationOMsg),
		MSG_BUY,
		NULL);

	//����MSG_PAY_TOLLS��Ϣ��������ɹ�·���¼�
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseLayer::receiveNotificationOMsg),
		MSG_PAY_TOLLS,
		NULL);

	//����MSG_RANDOM_ASK_EVENT��Ϣ�������ʺ�����¼�
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseLayer::receiveNotificationOMsg),
		MSG_RANDOM_ASK_EVENT,
		NULL);
	
	//����MSG_STRENGTH_UP��Ϣ��������������¼�
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseLayer::receiveNotificationOMsg),
		MSG_STRENGTH_UP,
		NULL);

	//����MSG_USE_SKILL��Ϣ������з���ɫʹ�ü����¼�
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseLayer::receiveNotificationOMsg),
		MSG_USE_SKILL,
		NULL);

	//������Ϸ������Ϣ
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseLayer::receiveNotificationOMsg),
		MSG_GAME_OVER,
		NULL);
}

void GameBaseLayer::receiveNotificationOMsg(Ref* pSender)
{
	auto msgStr = (__String*)pSender; 
	Vector<__String*> messageVector = Util::splitString(msgStr->getCString(),"-");
	int retMsgType = messageVector.at(0)->intValue();
	log("received go message is: %d",retMsgType); 

    Vector<Node*> menu = this->getMenu()->getChildren();

	if(messageVector.size()>3)    
	{
		if(messageVector.at(3)->intValue() == PLAYER_1_TAG)    //��ɫ1
		{
			//��¼��ɫ���ͣ��λ�õ����ܵ�����λ��
			player1->setStop_x(messageVector.at(1)->intValue());
			player1->setStop_y(messageVector.at(2)->intValue());
		}
		if(messageVector.at(3)->intValue() == PLAYER_2_TAG)    //��ɫ2
		{
			//��¼��ɫ���ͣ��λ�õ����ܵ�����λ��
			player2->setStop_x(messageVector.at(1)->intValue());
			player2->setStop_y(messageVector.at(2)->intValue());
		}
	}
		
	switch(retMsgType)
	{
	case MSG_GO_SHOW_TAG:              //���յ�����Ϣ��MSG_GO_SHOW_TAGʱ����ʾҪ��ʾgoMenuItem��
		{
			for(int i =0;i<menu.size();i++)
			{	
				Node* node = menu.at(i);
				node->runAction(MoveBy::create(0.3f,Vec2(-(node->getContentSize().width)*2,0)));
				diceSprite->resume();      //���ӻָ�ҡ��
				gameRoundCount++;          //����+1
				refresshRoundDisplay();    //���²���

				goMenuItem->setEnabled(true);    //go��ť���԰�
			}
			break;
		}		
	case MSG_GO_HIDE_TAG:      //���յ�����Ϣ��MSG_GO_HIDE_TAGʱ����ʾҪ����goMenuItem��
		{
			for(int i =0;i<menu.size();i++)
			{
				goMenuItem->setEnabled(false);     //go��ť�����԰�

				Node* node = menu.at(i);
				node->runAction(MoveBy::create(0.3f,Vec2(node->getContentSize().width*2,0)));
			}
			//��������
			__String *frameName = __String::createWithFormat("dice_%02d.png",randNumber);
			diceSprite->setSpriteFrame(diceFrameCache->getSpriteFrameByName(frameName->getCString()));
				
			diceSprite->pause();    //������ͣ
			break;
		}
	case MSG_BUY_BLANK_TAG:    //���յ�����Ϣ��MSG_BUY_BLANK_TAGʱ����ʾҪ����յ�
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerType = messageVector.at(3)->intValue();

			//���ݽ�ɫ�ֱ����������¼�
			switch(playerType)
			{
			case PLAYER_1_TAG:      
				showBuyLandDialog(MSG_BUY_BLANK_TAG);  //����ǽ�ɫ1 ���򵯳��Ի���
				transferLandTag = 0;
				break;
			case PLAYER_2_TAG:     //����ǽ�ɫ2����ֱ�ӹ��򣬲����Ź��򶯻�
				{
					//��Ч
					if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
					{
						int rand1 = rand()%(player2EffectVec_8.size());
						SimpleAudioEngine::getInstance()->playEffect(player2EffectVec_8.at(rand1)->getCString());
					}
					buyLand(MSG_BUY_BLANK_TAG,buy_land_x,buy_land_y,foot2Sprite,player2_building_1_tiledID,player2,PLAYER2_1_PARTICLE_PLIST);
					NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));  //���ý�ɫ������ʱ��������Ϣ������һ����ɫ�ж�
					break;
				}				
			}	
			break;
		}
	case MSG_BUY_LAND_1_TAG:         //������ͼ����ӡ��Ϊ���ǣ�
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerType = messageVector.at(3)->intValue();

			//���ݽ�ɫ�ֱ����������¼�
			switch(playerType)
			{
			case PLAYER_1_TAG:     
				showBuyLandDialog(MSG_BUY_LAND_1_TAG);  //����ǽ�ɫ1 ���򵯳��Ի���

				transferLandTag = 0;
				break;
			case PLAYER_2_TAG:     //����ǽ�ɫ2����ֱ�ӹ��򣬲����Ź��򶯻�
				{
					//��Ч
					if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
					{
						int rand1 = rand()%(player2EffectVec_7.size());
						SimpleAudioEngine::getInstance()->playEffect(player2EffectVec_7.at(rand1)->getCString());
					}
					//��������
					buyLand(MSG_BUY_LAND_1_TAG,buy_land_x,buy_land_y,star2Sprite,player2_building_2_tiledID,player2,PLAYER2_1_PARTICLE_PLIST);
					NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));  //���ý�ɫ������ʱ��������Ϣ������һ����ɫ�ж�
					break;
				}
			}
			break;
		}
	case MSG_BUY_LAND_2_TAG:         //������ͼ�����Ǳ�Ϊ����
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerType = messageVector.at(3)->intValue();

			//���ݽ�ɫ�ֱ����������¼�
			switch(playerType)
			{
			case PLAYER_1_TAG:      
				showBuyLandDialog(MSG_BUY_LAND_2_TAG);  //����ǽ�ɫ1 ���򵯳��Ի���

				transferLandTag = 0;
				break;
			case PLAYER_2_TAG:     //����ǽ�ɫ2����ֱ�ӹ��򣬲����Ź��򶯻�
				{
					//��Ч
					if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
					{
						int rand1 = rand()%(player2EffectVec_7.size());
						SimpleAudioEngine::getInstance()->playEffect(player2EffectVec_7.at(rand1)->getCString());
					}
					//��������
					buyLand(MSG_BUY_LAND_2_TAG,buy_land_x,buy_land_y,heart2Sprite,player2_building_3_tiledID,player2,PLAYER2_1_PARTICLE_PLIST);
					NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));  //���ý�ɫ������ʱ��������Ϣ������һ����ɫ�ж�
					break;
				}
			}
			break;
		}
	case MSG_PAY_TOLLS_1_TAG:     //����1�����ع�·��
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerType = messageVector.at(3)->intValue();
			payTolls(MSG_PAY_TOLLS_1_TAG,buy_land_x,buy_land_y,playerType);
			break;
		}
	case MSG_PAY_TOLLS_2_TAG:     //����2�����ع�·��
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerType = messageVector.at(3)->intValue();
			payTolls(MSG_PAY_TOLLS_2_TAG,buy_land_x,buy_land_y,playerType);
			break;
		}
	case MSG_PAY_TOLLS_3_TAG:    //����3�����ع�·��
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerType = messageVector.at(3)->intValue();
			payTolls(MSG_PAY_TOLLS_3_TAG,buy_land_x,buy_land_y,playerType);
			break;
		}
	case  MSG_RANDOM_ASK_EVENT_TAG:  //�ʺ�����¼�
		{
			int playerTag = messageVector.at(3)->intValue();
			switch(playerTag)
			{
			case PLAYER_1_TAG:
				doRandomAskEvent(player1);				
				this->scheduleOnce(schedule_selector(GameBaseLayer::sendMSGDealLandRound),TOAST_SHOW_TIME);
				break;
			case PLAYER_2_TAG:
				doRandomAskEvent(player2);
				this->scheduleOnce(schedule_selector(GameBaseLayer::sendMSGDealLandRound),TOAST_SHOW_TIME);
				break;
			}
			break;
		}
	case MSG_STRENGTH_UP30_TAG:     //�񵽻��ֿ����ָ�30����
		{
			int playerTag = messageVector.at(3)->intValue();
			doStrengthUpEvent(MSG_STRENGTH_UP30_TAG,playerTag);
			this->scheduleOnce(schedule_selector(GameBaseLayer::sendMSGDealLandRound),TOAST_SHOW_TIME);
			break;
		}

	case MSG_STRENGTH_UP50_TAG:     //�񵽻��ֿ����ָ�50����
		{
			int playerTag = messageVector.at(3)->intValue();
			doStrengthUpEvent(MSG_STRENGTH_UP50_TAG,playerTag);   //����
			this->scheduleOnce(schedule_selector(GameBaseLayer::sendMSGDealLandRound),TOAST_SHOW_TIME);
			break;
		}

	case MSG_STRENGTH_UP80_TAG:     //�񵽻��ֿ����ָ�80����
		{
			int playerTag = messageVector.at(3)->intValue();
			doStrengthUpEvent(MSG_STRENGTH_UP80_TAG,playerTag);    //����
			this->scheduleOnce(schedule_selector(GameBaseLayer::sendMSGDealLandRound),TOAST_SHOW_TIME);
			break;
		}

	case MSG_USE_SKILL_TAG:   //�з���ɫʹ�ü���
		{
			//��ȡ��ɫ��tag   
            int playerTag = messageVector.at(3)->intValue();  
            //��ɫҪʹ�õļ���  
            int kill_index =  messageVector.at(4)->intValue();  
            //ʹ�ü�����Ҫ�ķѵ�����  
            int needLostStrength = messageVector.at(5)->intValue();  
            //��ǰ�ؿ�ĵȼ�  
            int landLevel = messageVector.at(6)->intValue();  

			if(playerTag == PLAYER_2_TAG)  
            {  
                //�ý�ɫ������Ӧ������    
				refreshStrength(player2,-needLostStrength);  
				Vec2 pointOfGL = Util::map2GL(Vec2(player2->getStop_x(),player2->getStop_y()),_map);  
                //���ż�����Ӧ����  
                switch(kill_index)  
                {  
                case 0://��������  
					{ 
						//��Ч
						if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
						{
							int rand1 = rand()%(player2EffectVec_4.size());
							SimpleAudioEngine::getInstance()->playEffect(player2EffectVec_4.at(rand1)->getCString());
							nextPlayerEffectVec = player1EffectVec_5;
							this->scheduleOnce(schedule_selector(GameBaseLayer::playNextEffectVec),2.0f);
						}
						auto rainSprite = Sprite::createWithSpriteFrame(player2->getRain_skill_animate()->getAnimation()->getFrames().at(0)->getSpriteFrame());  
                        rainSprite->setAnchorPoint(Vec2(0,0));  
                        rainSprite->setPosition(pointOfGL+Vec2(-tiledWidth/2,tiledHeight/2)); 
						this->addChild(rainSprite);  
                        
                        //��������,��Ϻ����õؿ�Ϊ�յؿ顣�����ͽ�ɫ�������ߵ���Ϣ  
                        rainSprite->runAction(Sequence::create(
							player2->getRain_skill_animate(),
							CallFunc::create([this,rainSprite]()  
							{  
								landLayer->setTileGID(blank_land_tiledID,Vec2(player2->getStop_x(),player2->getStop_y()));      
								rainSprite->removeFromParent();  
								NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,__String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));  
							}),NULL));  
                        break;  
                    } 
                case 1://��ȡ����  
                    {  
						//��Ч
						if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
						{
							int rand1 = rand()%(player2EffectVec_2.size());
							SimpleAudioEngine::getInstance()->playEffect(player2EffectVec_2.at(rand1)->getCString());
							nextPlayerEffectVec = player1EffectVec_3;
							this->scheduleOnce(schedule_selector(GameBaseLayer::playNextEffectVec),2.0f);
						}

						auto transferSprite = Sprite::createWithSpriteFrame(player2->getTransfer_skill_animate()->getAnimation()->getFrames().at(0)->getSpriteFrame());  
						transferSprite->setAnchorPoint(Vec2(0,0));  
                        transferSprite->setPosition(pointOfGL);  
						this->addChild(transferSprite);  
                                       
                        //����������Ϻ����õؿ�Ϊ�Լ���Ӧ�ȼ��ؿ顣�����ͽ�ɫ�������ߵ���Ϣ  
                        transferSprite->runAction(Sequence::create(
							player2->getTransfer_skill_animate(),
							CallFunc::create([this,landLevel,transferSprite]()  
							{  
								landLayer->setTileGID(landLevel,Vec2(player2->getStop_x(),player2->getStop_y()));   
								transferSprite->removeFromParent();  
								NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,__String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));  
							}),NULL));  
                        break;  
                    }  
                }
			}
			break;	
		}
	case MSG_GAME_OVER_TAG:
		{
			int playerType = messageVector.at(3)->intValue();
			/*
			if(playerType == PLAYER_1_TAG)   //����ǽ�ɫ1��������
			{
				auto scene = Scene::create();
				auto layer = GameOverLayer::createScene(MSG_LOSE_TAG);
				scene->addChild(layer);
				Director::getInstance()->replaceScene(scene);
			}	
			else
			{
				auto scene = Scene::create();
				auto layer = GameOverLayer::createScene(MSG_WIN_TAG);
				scene->addChild(layer);
				Director::getInstance()->replaceScene(scene);
			}
			break;
			*/
			if(playerType == PLAYER_2_TAG)  
			{
				//��������Ч��
				ParticleSystem *particle = ParticleSystemQuad::create("images/win_particle.plist");
				particle->setPosition(Vec2(winSize.width/2,winSize.height/2));
				this->addChild(particle);

				auto winSprite = Sprite::create("images/win.png");
				winSprite->setPosition(Vec2(winSize.width/2,winSize.height/2));
				this->addChild(winSprite);
			}
			else
			{				
				auto loseSprite = Sprite::create("images/lose.png");
				loseSprite->setPosition(Vec2(winSize.width/2,winSize.height/2));
				this->addChild(loseSprite);
			}
			break;
		}
	}
}


void GameBaseLayer::sendMSGDealLandRound(float dt)
{
	NotificationCenter::getInstance()->postNotification(MSG_AROUND_LAND,__String::createWithFormat("%d",MSG_AROUND_LAND_TAG));  //������Ϣ�����������ػ�ɷ�	
}

void GameBaseLayer::sendMSGPickOneToGO(float dt)
{
	NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,__String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));  //������Ϣ������һ����ɫ�ж�
}

void GameBaseLayer::initRandomAskEventMap()
{
	randomAskEventMap.insert(TAX_REBATES_TAG,__String::create(TAX_REBATES));
    randomAskEventMap.insert(PAY_TAXES_TAG,__String::create(PAY_TAXES));
    randomAskEventMap.insert(LOSS_STRENGTH_TAG,__String::create(LOSS_STRENGTH));
    randomAskEventMap.insert(PHYSICAL_RECOVERY_TAG,__String::create(PHYSICAL_RECOVERY));
    randomAskEventMap.insert(INVESTMENT_DIVIDENDS_TAG,__String::create(INVESTMENT_DIVIDENDS));
    randomAskEventMap.insert(INVESTMENT_LOSS_TAG,__String::create(INVESTMENT_LOSS));
}

//����񵽻��ֿ������������¼�
void GameBaseLayer::doStrengthUpEvent(int strengthUp,int playerTag)
{
	//��Ч
	if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(PARTICLE_EFFECT);
	}
	int strengthValue = 0;

	switch(strengthUp)
	{
	case MSG_STRENGTH_UP30_TAG:
		strengthValue = 30;
		break;
	case MSG_STRENGTH_UP50_TAG:
		strengthValue = 50;
		break;
	case MSG_STRENGTH_UP80_TAG:
		strengthValue = 80;
		break;
	}

	switch(playerTag)
	{
	case PLAYER_1_TAG:
		{
			strengthUpSprite->setVisible(true);   
			strengthUpSprite->setPosition(player1->getPosition());
			auto action = Sequence::create(
					strengthUpAnimate,
					CallFunc::create([this](){
						strengthUpSprite->setVisible(false);
					}),
					NULL);
			strengthUpSprite->runAction(action);     //����������������
			//��ʾ��Ϣ
			CocosToast::createToast(
				this,
				__String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(STRENGTH_UP)->getCString(),strengthValue)->getCString(),
				TOAST_SHOW_TIME,
				player1->getPosition());     

			refreshStrength(player1,strengthValue);       //����������ʾ
			break;
		}
		
	case PLAYER_2_TAG:
		{
			strengthUpSprite->setVisible(true);   
			strengthUpSprite->setPosition(player2->getPosition());
			auto action = Sequence::create(
					strengthUpAnimate,
					CallFunc::create([this](){
						strengthUpSprite->setVisible(false);
					}),
					NULL);
			strengthUpSprite->runAction(action);     //����������������

			//��ʾ��Ϣ
			CocosToast::createToast(
				this,
				__String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(STRENGTH_UP)->getCString(),strengthValue)->getCString(),
				TOAST_SHOW_TIME,
				player2->getPosition());     

			refreshStrength(player2,strengthValue);       //����������ʾ
			break;
		}
	}
}

void GameBaseLayer::doRandomAskEvent(RicherPlayer *player)
{
	int randomNumber = rand()%(randomAskEventMap.size()) + 1;  //���һ�����֣�1~Map��������

	switch(randomNumber)
	{
	case TAX_REBATES_TAG:
		refreshMoney(player,10000);       //��������Ͷ�ʣ�����˰��10000
		break;
	case PAY_TAXES_TAG:
		{
			//��Ч
			if(player->getTag() == PLAYER_1_TAG)
			{
				if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
				{
					int rand1 = rand()%(player2EffectVec_9.size());
					SimpleAudioEngine::getInstance()->playEffect(player2EffectVec_9.at(rand1)->getCString());
				}
			}
			else if(player->getTag() == PLAYER_2_TAG)
			{
				if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
				{
					int rand1 = rand()%(player1EffectVec_9.size());
					SimpleAudioEngine::getInstance()->playEffect(player1EffectVec_9.at(rand1)->getCString());
				}
			}
			refreshMoney(player,-20000);      //�����ϲ����񣬲���˰��20000
			break;
		}
	case LOSS_STRENGTH_TAG:
		refreshStrength(player,-100);     //�ȵ��پƣ�������к�������Ĺ�
		break;
	case PHYSICAL_RECOVERY_TAG:
		refreshStrength(player,+100);     //���˴��裬�����ָ�
		break;
	case INVESTMENT_DIVIDENDS_TAG:
		refreshMoney(player,20000);       //Ͷ�ʻ������ֺ�20000
		break;
	case INVESTMENT_LOSS_TAG:
		refreshMoney(player,-30000);      //Ͷ��ʧ�ܣ�����30000
		break;
	}

	__String *str = randomAskEventMap.at(randomNumber);
	CocosToast::createToast(
		this,
		LanguageString::getInstance()->getLanguageString(str->getCString())->getCString(),
		TOAST_SHOW_TIME,
		player->getPosition());    //Toast��ʾ�¼���Ϣ
}

void GameBaseLayer::buyLand(int buyTag,float x,float y,Sprite *landSprite,int landLevel,RicherPlayer *player,char *particlelistName)
{
	int money = 0;
	//�жϹ���������Ҫ����Ǯ
	if(buyTag == MSG_BUY_BLANK_TAG)
	{
		money = LAND_BLANK_MONEY;
	}
	if(buyTag == MSG_BUY_LAND_1_TAG)
	{
		money = LAND_LEVEL_1_MONEY;
	}
	if(buyTag == MSG_BUY_LAND_2_TAG)
	{
		money = LAND_LEVEL_2_MONEY;
	}
	Vec2 pointOfMap = Vec2(x,y);
	Vec2 pointOfGL = Util::map2GL(pointOfMap,GameBaseLayer::_map);

	landSprite->setVisible(true);
	landSprite->setPosition(pointOfGL);
	landSprite->runAction(Sequence::create(
		scaleBy1ForBuyLand,
		scaleBy2ForBuyLand,
		CallFunc::create([this,pointOfMap,pointOfGL,particlelistName,x,y,landSprite,landLevel,player,money]()
			{
				playParticle(pointOfGL,particlelistName);
				landSprite->setVisible(false);
				landLayer->setTileGID(landLevel,Vec2(x,y));
				refreshMoney(player,-money);
				}),
			NULL));		
}

void GameBaseLayer::payTolls(int payTollTag,float x,float y,int playerTag)
{
	int money =0;
	//�жϽ��ɹ�·�ѵļ���
	if(payTollTag == MSG_PAY_TOLLS_1_TAG)
	{
		money = LAND_BLANK_MONEY;      
	}
	else if(payTollTag == MSG_PAY_TOLLS_2_TAG)
	{
		money = LAND_LEVEL_1_MONEY;
	}
	else if(payTollTag == MSG_PAY_TOLLS_3_TAG)
	{
		money = LAND_LEVEL_2_MONEY;
	}

	RicherPlayer *landPlayer = getPlayerByTiled(x,y);

	if(playerTag ==PLAYER_1_TAG)    //����ǽ�ɫ1���ɵĻ����ͽ�ɫ1��Ǯ�����������߼�Ǯ
	{
		//��Ч
		if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
		{
			int rand1 = rand()%(player1EffectVec_1.size());
			SimpleAudioEngine::getInstance()->playEffect(player1EffectVec_1.at(rand1)->getCString());
			nextPlayerEffectVec = player2EffectVec_6;
			this->scheduleOnce(schedule_selector(GameBaseLayer::playNextEffectVec),2.0f);
		}
		refreshMoney(player1,-money);
		refreshMoney(landPlayer,money);
		CocosToast::createToast(this,__String::createWithFormat("-%d",money)->getCString(),TOAST_SHOW_TIME,player1->getPosition());
		CocosToast::createToast(this,__String::createWithFormat("+%d",money)->getCString(),TOAST_SHOW_TIME,landPlayer->getPosition());

		transferLandTag = payTollTag;
	}
	else if(playerTag ==PLAYER_2_TAG)   //����ǽ�ɫ2���ɵĻ����ͽ�ɫ1��Ǯ�����������߼�Ǯ
	{
		//��Ч
		if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
		{
			int rand1 = rand()%(player2EffectVec_1.size());
			SimpleAudioEngine::getInstance()->playEffect(player2EffectVec_1.at(rand1)->getCString());
			nextPlayerEffectVec = player1EffectVec_6;
			this->scheduleOnce(schedule_selector(GameBaseLayer::playNextEffectVec),2.0f);
		}
		refreshMoney(player2,-money);
		refreshMoney(landPlayer,money);
		CocosToast::createToast(this,__String::createWithFormat("-%d",money)->getCString(),TOAST_SHOW_TIME,player2->getPosition());
		CocosToast::createToast(this,__String::createWithFormat("+%d",money)->getCString(),TOAST_SHOW_TIME,landPlayer->getPosition());
	}
	this->scheduleOnce(schedule_selector(GameBaseLayer::sendMSGPickOneToGO),TOAST_SHOW_TIME);
}

RicherPlayer* GameBaseLayer::getPlayerByTiled(float x,float y)
{
	int gid = landLayer->getTileGIDAt(Vec2(x,y));
	if(gid == player1_building_1_tiledID || gid == player1_building_2_tiledID || gid == player1_building_3_tiledID)    //�ж��ǲ��ǽ�ɫ1������
	{
		return player1;
	}

	if(gid == player2_building_1_tiledID || gid == player2_building_2_tiledID || gid == player2_building_3_tiledID)     //�ж��ǲ��ǽ�ɫ2������
	{
		return player2;
	}
	return nullptr;
}

void GameBaseLayer::refreshMoney(RicherPlayer *player,int money)
{
	player->setMoney(player->getMoney() + money);
	if(player->getTag() == PLAYER_1_TAG)
	{
		__String *moeny1 = __String::createWithFormat("$%d",player->getMoney());
		getPlayer1_money_label()->setString(moeny1->getCString());
	}
	if(player->getTag() == PLAYER_2_TAG)
	{
		__String *moeny2 = __String::createWithFormat("$%d",player->getMoney());
		getPlayer2_money_label()->setString(moeny2->getCString());
	}
}

void GameBaseLayer::refreshStrength(RicherPlayer *player,int strength)
{
	player->setStrength(player->getStrength() + strength);
	if(player->getTag() == PLAYER_1_TAG)
	{
		if(player->getStrength()>=0)
		{
			__String *strength1 = __String::createWithFormat("+%d",player->getStrength());
			getPlayer1_strength_label()->setString(strength1->getCString());
		}
		else
		{
			__String *strength1 = __String::createWithFormat("%d",player->getStrength());
			getPlayer1_strength_label()->setString(strength1->getCString());
		}
		
	}
	if(player->getTag() == PLAYER_2_TAG)
	{
		if(player->getStrength()>=0)
		{
			__String *strength2 = __String::createWithFormat("+%d",player->getStrength());
			getPlayer2_strength_label()->setString(strength2->getCString());
		}
		else
		{
			__String *strength2 = __String::createWithFormat("%d",player->getStrength());
			getPlayer2_strength_label()->setString(strength2->getCString());
			}
	}
}

void GameBaseLayer::addPathMark()
{
	Sprite* mark1 = Sprite::create(PATH_MARK_1);
	Sprite* mark2 = Sprite::create(PATH_MARK_2);
	Sprite* mark3 = Sprite::create(PATH_MARK_3);
	Sprite* mark4 = Sprite::create(PATH_MARK_4);
	Sprite* mark5 = Sprite::create(PATH_MARK_5);
	Sprite* mark6 = Sprite::create(PATH_MARK_6);

	mark1->setAnchorPoint(Vec2(0,0));
	mark2->setAnchorPoint(Vec2(0,0));
	mark3->setAnchorPoint(Vec2(0,0));
	mark4->setAnchorPoint(Vec2(0,0));
	mark5->setAnchorPoint(Vec2(0,0));
	mark6->setAnchorPoint(Vec2(0,0));

	addChild(mark1);
	addChild(mark2);
	addChild(mark3);
	addChild(mark4);
	addChild(mark5);
	addChild(mark6);

	pathMarkVector.pushBack(mark1);
	pathMarkVector.pushBack(mark2);
	pathMarkVector.pushBack(mark3);
	pathMarkVector.pushBack(mark4);
	pathMarkVector.pushBack(mark5);
	pathMarkVector.pushBack(mark6);
}

void GameBaseLayer::drawPathMark(std::vector<int> rowVector,std::vector<int> colVector)
{
	for(int i =0;i<rowVector.size()-1;i++)
	{
		pathMarkVector.at(i)->setPosition(Vec2(colVector[i+1]*32,rowVector[i+1]*32));
		pathMarkVector.at(i)->setVisible(true);
	}
}


void GameBaseLayer::addDigiteRoundSprite()
{
	gameRoundCount = 0 ;
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("map/digital_round.plist");
	for(int i=0;i<10;i++)
	{
		__String *frameName = __String::createWithFormat("digital_%d.png",i);
		digitalRoundVector.pushBack(frameCache->getSpriteFrameByName(frameName->getCString()));
	}	
}


void GameBaseLayer::refresshRoundDisplay()
{
	for(int i=0;i<refreshRoundVector.size();i++)
	{
		refreshRoundVector.at(i)->setVisible(false);
	}

	refreshRoundVector.clear();

	int count = gameRoundCount;
	Sprite *st;

	//��Ϸ��ʼʱ���غ�Ϊ0
	if(count == 0)
	{
		st = Sprite::createWithSpriteFrame(digitalRoundVector.at(0));		
		this->addChild(st);
		refreshRoundVector.pushBack(st);
	}
	//���غ���ת����sprite����Ŷ�������
	while(count>0)
	{
		st = Sprite::createWithSpriteFrame(digitalRoundVector.at(count%10));     //�ȴӸ�λ����ʼ��
		refreshRoundVector.pushBack(st);
		this->addChild(st);
		count = count/10;
	}

	refreshRoundVector.reverse();   //��Ϊ���ʱ���ǵ����ŵģ�����Ҫ��˳�򵹻���

	for(int i = 0; i<refreshRoundVector.size();i++)
	{
		refreshRoundVector.at(i)->setPosition(Vec2((tableStartPosition_x + 50)+ (i*25),50));
		refreshRoundVector.at(i)->setAnchorPoint(Vec2(0,1));
		refreshRoundVector.at(i)->setVisible(true);
	}
}


void GameBaseLayer::buyLandCallBack(Node* node)
{
	if(node->getTag() == Btn_OK_TAG)
	{
		switch(popDialog->getDataTag())
		{		
		case MSG_BUY_BLANK_TAG:
			//��Ч
			if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
			{
				int rand1 = rand()%(player1EffectVec_8.size());
				SimpleAudioEngine::getInstance()->playEffect(player1EffectVec_8.at(rand1)->getCString());
			}
			buyLand(MSG_BUY_BLANK_TAG,buy_land_x,buy_land_y,foot1Sprite,player1_building_1_tiledID,player1,PLAYER1_1_PARTICLE_PLIST);				
			break;			
		case MSG_BUY_LAND_1_TAG:
			//��Ч
			if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
			{
				int rand1 = rand()%(player1EffectVec_7.size());
				SimpleAudioEngine::getInstance()->playEffect(player1EffectVec_7.at(rand1)->getCString());
			}
			buyLand(MSG_BUY_LAND_1_TAG,buy_land_x,buy_land_y,star1Sprite,player1_building_2_tiledID,player1,PLAYER1_1_PARTICLE_PLIST);
			break;
		case MSG_BUY_LAND_2_TAG:
			//��Ч
			if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
			{
				int rand1 = rand()%(player1EffectVec_7.size());
				SimpleAudioEngine::getInstance()->playEffect(player1EffectVec_7.at(rand1)->getCString());
			}
			buyLand(MSG_BUY_LAND_2_TAG,buy_land_x,buy_land_y,heart1Sprite,player1_building_3_tiledID,player1,PLAYER1_1_PARTICLE_PLIST);
			break;	
		}
		//������Ϻ��öԻ�����ʧ����������Ϣ����������ɫ����  
		popDialog->removeFromParent();		
		this->scheduleOnce(schedule_selector(GameBaseLayer::sendMSGPickOneToGO),1.0f);
	}
	else
	{
		//���ȡ�����öԻ�����ʧ����������Ϣ����������ɫ����  
		popDialog->removeFromParent(); 
        NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));
	}
}

void GameBaseLayer::initPopDialog()
{
	popDialog = PopupLayer::create(DIALOG_BG);
	popDialog->setContentSize(Size(Dialog_Size_Width,Dialog_Size_Height));
	popDialog->setTitle(LanguageString::getInstance()->getLanguageString(DIALOG_TITLE)->getCString());
	popDialog->setContentText("",20,60,250);
	popDialog->setCallbackFunc(this,callfuncN_selector(GameBaseLayer::buyLandCallBack));
	popDialog->addButton(BUTTON_BG1,BUTTON_BG3,LanguageString::getInstance()->getLanguageString(OK)->getCString(),Btn_OK_TAG);
	popDialog->addButton(BUTTON_BG1,BUTTON_BG3,LanguageString::getInstance()->getLanguageString(CANCEL)->getCString(),Btn_Cancel_TAG);
	this->addChild(popDialog);
}

void GameBaseLayer::showBuyLandDialog(int landTag)
{
	initPopDialog();
	__String *showContentText;
	switch(landTag)
	{
	case MSG_BUY_BLANK_TAG:
		//����յأ���ʾ����Ϣ
		showContentText = __String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(BUY_LAND_MSG)->getCString(),LAND_BLANK_MONEY);
		break;
	case MSG_BUY_LAND_1_TAG:
		//�������أ���ʾ����Ϣ
		showContentText = __String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(BUY_LAND_MSG)->getCString(),LAND_LEVEL_1_MONEY);
		break;
	case MSG_BUY_LAND_2_TAG:
		//�������أ���ʾ����Ϣ
		showContentText = __String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(BUY_LAND_MSG)->getCString(),LAND_LEVEL_2_MONEY);
		break;
	}
	popDialog->getLabelContentText()->setString(showContentText->getCString());
	popDialog->setDataTag(landTag);
	
}

//�������
void GameBaseLayer::addDice()
{
	diceFrameCache = SpriteFrameCache::getInstance();
	diceFrameCache->addSpriteFramesWithFile("map/dice.plist","map/dice.png");
	Vector<SpriteFrame*> diceVector;

	for(int i=1;i<=6;i++)
	{
		__String *frameName = __String::createWithFormat("dice_%02d.png",i);
		diceVector.pushBack(diceFrameCache->getSpriteFrameByName(frameName->getCString()));
	}
	if(!AnimationCache::getInstance()->getAnimation("dice_animation"))
	{
		AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(diceVector,0.1),"dice_animation");
	}
	diceAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("dice_animation"));
	diceAnimate->retain();

	diceSprite = Sprite::createWithSpriteFrame(diceFrameCache->getSpriteFrameByName("dice_01.png"));
	diceSprite->setPosition(Vec2(tableStartPosition_x + 1.5*tableWidth, tableStartPosition_y - tableHeight*5));
	this->addChild(diceSprite);
	
	diceSprite->runAction(RepeatForever::create(diceAnimate));
}

void GameBaseLayer::addPlayerStrengthUpAniate()
{	
	strengthUpFrameCache = SpriteFrameCache::getInstance();
	strengthUpFrameCache->addSpriteFramesWithFile("images/strength_up.plist","images/strength_up.png");
	Vector<SpriteFrame*> strengthUpSprite_vector;      //��������������������

	for(int i =1;i<=14;i++)
	{
		__String *framename = __String::createWithFormat("strength_up_%02d.png",i);
		strengthUpSprite_vector.pushBack(strengthUpFrameCache->getSpriteFrameByName(framename->getCString()));
	}
	auto animation = Animation::createWithSpriteFrames(strengthUpSprite_vector,0.1f);
	strengthUpAnimate = Animate::create(animation);
	strengthUpAnimate->retain();

	strengthUpSprite = Sprite::createWithSpriteFrame(strengthUpFrameCache->getSpriteFrameByName("strength_up_01.png"));
	strengthUpSprite->setAnchorPoint(Vec2(0,0.5));
	this->addChild(strengthUpSprite);
}

void GameBaseLayer::initLandLayerFromMap()
{
	landLayer = _map->getLayer("land");
}

void GameBaseLayer::particleForBuyLand()
{
	//1������--��ӡ�Ķ���

	scaleBy1ForBuyLand = ScaleBy::create(0.1,1.5);    //�Ŵ�
	scaleBy2ForBuyLand = ScaleBy::create(0.5,0.7);    //��С
	scaleBy1ForBuyLand->retain();
	scaleBy2ForBuyLand->retain();

	foot1Sprite = Sprite::create(PLAYER1_1_PARTICLE_PNG);    //��ӡ����
	foot1Sprite->setAnchorPoint(Vec2(0,0));
	this->addChild(foot1Sprite);

	foot2Sprite = Sprite::create(PLAYER2_1_PARTICLE_PNG);
	foot2Sprite->setAnchorPoint(Vec2(0,0));
	this->addChild(foot2Sprite);

	//2������--���ǵĶ���
	landFadeOut = FadeOut::create(0.1);    //����
	landFadeIn = FadeIn::create(0.1);      //����
	landFadeIn->retain();
	landFadeOut->retain();

	star1Sprite = Sprite::create(PLAYER1_2_PARTICLE_PNG);
	star1Sprite->setAnchorPoint(Vec2(0,0));
	this->addChild(star1Sprite);

	star2Sprite = Sprite::create(PLAYER2_2_PARTICLE_PNG);
	star2Sprite->setAnchorPoint(Vec2(0,0));
	this->addChild(star2Sprite);

	//3������--���εĶ���
	heart1Sprite = Sprite::create(PLAYER1_3_PARTICLE_PNG);
	heart1Sprite->setAnchorPoint(Vec2(0,0));
	this->addChild(heart1Sprite);

	heart2Sprite = Sprite::create(PLAYER2_3_PARTICLE_PNG);
	heart2Sprite->setAnchorPoint(Vec2(0,0));
	this->addChild(heart2Sprite);
}

void GameBaseLayer::playParticle(cocos2d::Vec2 point,char *plistName)
{
	//����Ч��
	ParticleSystem *particleSystem_foot = ParticleSystemQuad::create(plistName);
	particleSystem_foot->retain();
	ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(particleSystem_foot->getTexture());
	batch->addChild(particleSystem_foot);
	this->addChild(batch);

	particleSystem_foot->setPosition(point + Vec2(tiledWidth/2,tiledHeight/2));
	particleSystem_foot->release();
}

void GameBaseLayer::initAudioEffect()
{
	//����·������0-6
	player2EffectVec_1.pushBack(String::create(P2_SPEAKING01));
	player2EffectVec_1.pushBack(String::create(P2_QISIWOLE));
	player2EffectVec_1.pushBack(String::create(P2_XINHAOKONGA));
	player2EffectVec_1.pushBack(String::create(P2_BUHUIBA));
	player2EffectVec_1.pushBack(String::create(P2_PAYHIGH));
	player2EffectVec_1.pushBack(String::create(P2_QIANGQIANA));
	player2EffectVec_1.pushBack(String::create(P2_HEBAOCHUXIE));

	//������˵ؿ�7-10
	player2EffectVec_2.pushBack(String::create(P2_BIEGUAIWO));
	player2EffectVec_2.pushBack(String::create(P2_SPEAKING02));
	player2EffectVec_2.pushBack(String::create(P2_TIGER));
	player2EffectVec_2.pushBack(String::create(P2_NIDEJIUSHODE));
	
	//���ݱ�����11-14
	player2EffectVec_3.pushBack(String::create(P2_ZHENMIANMU));
	player2EffectVec_3.pushBack(String::create(P2_WODEDIQI));
	player2EffectVec_3.pushBack(String::create(P2_HAOQIFU));
	player2EffectVec_3.pushBack(String::create(P2_WANGFA));

	//�ݻٱ��˷���15-18
	player2EffectVec_4.pushBack(String::create(P2_NIGAIWOCHAI));
	player2EffectVec_4.pushBack(String::create(P2_KANWODE));
	player2EffectVec_4.pushBack(String::create(P2_HAIRENLE));
	player2EffectVec_4.pushBack(String::create(P2_BAOCHOU));
	
	//���ݱ��ݻ�19-22
	player2EffectVec_5.pushBack(String::create(P2_WODEYANGFANG));
	player2EffectVec_5.pushBack(String::create(P2_QIFURENJIA));
	player2EffectVec_5.pushBack(String::create(P2_SHAQIANDAO));
	player2EffectVec_5.pushBack(String::create(P2_LIANXIANGXIYU));
	player2EffectVec_5.pushBack(String::create(P2_HAOJIUGAIHAO));

	//��ȡ��·��23 - 28
	player2EffectVec_6.pushBack(String::create(P2_RENBUWEIJI));
	player2EffectVec_6.pushBack(String::create(P2_XIAOQI));
	player2EffectVec_6.pushBack(String::create(P2_RONGXING));
	player2EffectVec_6.pushBack(String::create(P2_MANYI));
	player2EffectVec_6.pushBack(String::create(P2_XIAOFUPO));
	player2EffectVec_6.pushBack(String::create(P2_DUOGEI));

	//��������29-30
	player2EffectVec_7.pushBack(String::create(P2_HIGHER));
	player2EffectVec_7.pushBack(String::create(P2_WANZHANGGAOLOU));

	//���31 - 34
	player2EffectVec_8.pushBack(String::create(P2_BUYIT));
	player2EffectVec_8.pushBack(String::create(P2_HAODEKAISHI));
	player2EffectVec_8.pushBack(String::create(P2_RANGNIZHU));
	player2EffectVec_8.pushBack(String::create(P2_MAIWOBA));

	//�Է�������˰35-38
	player2EffectVec_9.pushBack(String::create(P2_TOUSHUI));
	player2EffectVec_9.pushBack(String::create(P2_FALVZHICAI));
	player2EffectVec_9.pushBack(String::create(P2_GUOKU));
	player2EffectVec_9.pushBack(String::create(P2_NASHUI));



	//����·������
	player1EffectVec_1.pushBack(String::create(P1_Speaking_00435));
	player1EffectVec_1.pushBack(String::create(P1_Speaking_00461));
	player1EffectVec_1.pushBack(String::create(P1_Speaking_00475));
	player1EffectVec_1.pushBack(String::create(P1_Speaking_01060));
	player1EffectVec_1.pushBack(String::create(P1_Speaking_01062));

	//������˵ؿ�
	player1EffectVec_2.pushBack(String::create(P1_Speaking_00429));

	//���ݱ�����
	player1EffectVec_3.pushBack(String::create(P1_Speaking_00430));
	player1EffectVec_3.pushBack(String::create(P1_Speaking_00464));
	player1EffectVec_3.pushBack(String::create(P1_Speaking_00469));
	player1EffectVec_3.pushBack(String::create(P1_Speaking_00470));
	player1EffectVec_3.pushBack(String::create(P1_Speaking_00476));

	//�ݻٱ��˷���
	player1EffectVec_4.pushBack(String::create(P1_Speaking_00433));
	player1EffectVec_4.pushBack(String::create(P1_Speaking_00437));

	//���ݱ��ݻ�
	player1EffectVec_5.pushBack(String::create(P1_Speaking_00462));
	player1EffectVec_5.pushBack(String::create(P1_Speaking_00463));
	player1EffectVec_5.pushBack(String::create(P1_Speaking_00466));
	player1EffectVec_5.pushBack(String::create(P1_Speaking_00468));
	player1EffectVec_5.pushBack(String::create(P1_Speaking_00474));
	player1EffectVec_5.pushBack(String::create(P1_Speaking_01061));

	//��ȡ��·��
	player1EffectVec_6.pushBack(String::create(P1_Speaking_00453));
	player1EffectVec_6.pushBack(String::create(P1_Speaking_01059));
	player1EffectVec_6.pushBack(String::create(P1_Speaking_01057));
	//��������
	player1EffectVec_7.pushBack(String::create(P1_Speaking_01051));
	player1EffectVec_7.pushBack(String::create(P1_Speaking_01066));

	//���
	player1EffectVec_8.pushBack(String::create(P1_Speaking_00458));
	player1EffectVec_8.pushBack(String::create(P1_Speaking_01067));

	//�Է�������˰
	player1EffectVec_9.pushBack(String::create(P1_Speaking_00452));

}


void GameBaseLayer::playNextEffectVec(float t)
{
	if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
	{
		int rand1 = rand()%(nextPlayerEffectVec.size());
		SimpleAudioEngine::getInstance()->playEffect(nextPlayerEffectVec.at(rand1)->getCString());
	}
}
