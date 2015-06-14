#include "GameBaseScene.h"

USING_NS_CC;
     //static 变量在类外初始化
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
	//addMap();                //添加地图
	addRightBanner();	     //添加右边的表格
	drawTable(2);	         //画表格
	addDigiteRoundSprite();  //添加数字精灵
	refresshRoundDisplay();  //更新回合计数
	addGoButton();           //添加Go按钮
	//initTiledGrid();         //初始化地图二维数组，由于每个关卡的地图大小不一样，所以这个函数在子类中实现
	setWayPassToGrid();      //根据图层way，设置canPassGrid数组相应的值为true
	addPathMark();           //添加路径标记
	addPlayer();             //添加角色
	addDice();               //添加骰子
	addNotificationObserver();  //添加消息接收器
	gameRoundCount = 0 ;     //初始化回合数
	initLandLayerFromMap();  //初始化land层
	
	//initPropTiledID();       //初始化道具ID,由于每个关卡的地图大小不一样，所以这个函数在子类中实现

	particleForBuyLand();    //加载脚印精灵的动作
	initRandomAskEventMap(); //初始化Map容器，存放问号随机事件
	addPlayerStrengthUpAniate();  //添加体力回升的动作

	initAudioEffect();    //添加音效到容器中
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
		//////////画表格start//////////
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
	//////////画表格end//////////
}

void GameBaseLayer::addPlayer()
{
	addPlayerInfo();

	/////////添加角色到地图的随机位置////////////

	//指定随机数种子，随机数依据这个种子产生 采用当前时间生成随机种子：
	struct timeval now;
	gettimeofday(&now,NULL);//计算时间种子
	unsigned rand_seed =(unsigned)(now.tv_sec*1000 + now.tv_usec/1000);// 初始化随机数   
	srand(rand_seed);

	//角色1
	player1 = RicherPlayer::create(PLAYER_1_NAME,PLAYER_1_TAG,false);	
	int _rand1 =rand()%(wayLayerPass_Vector.size());       //获取一个0~容器容量之间的随机数
	Vec2 vec2ForPlayer1 = wayLayerPass_Vector.at(_rand1);
	//这个我们给纵向位置添加一个tiledHeight高度，目的是为了让角色居中显示在道路中
    vec2ForPlayer1.y +=tiledHeight; 
	player1->setPosition(vec2ForPlayer1);
	player1->setAnchorPoint(Vec2(0,0.5));

	char money1[20];
	memset(money1,0,20);
	sprintf(money1,"$%d",player1->getMoney());
	player1_money_label->setString(money1);                   //显示角色金钱

	char strength1[20];
	memset(strength1,0,20);
	sprintf(strength1,"+%d",player1->getStrength());
	player1_strength_label->setString(strength1);                //显示角色体力

	this->addChild(player1);
	players_vector.pushBack(player1);

	//角色2
	player2 = RicherPlayer::create(PLAYER_2_NAME,PLAYER_2_TAG,true);
	int _rand2 =rand()%(wayLayerPass_Vector.size());       //获取一个0~容器容量之间的随机数
	Vec2 vec2ForPlayer2 = wayLayerPass_Vector.at(_rand2);
	//这个我们给纵向位置添加一个tiledHeight高度，目的是为了让角色居中显示在道路中
    vec2ForPlayer2.y +=tiledHeight; 
	player2->setPosition(vec2ForPlayer2);
	player2->setAnchorPoint(Vec2(0,0.5));

	char money2[20];
	memset(money2,0,20);
	sprintf(money2,"$%d",player2->getMoney());
	player2_money_label->setString(money2);                   //显示角色金钱

	char strength2[20];
	memset(strength2,0,20);
	sprintf(strength2,"+%d",player2->getStrength());
	player2_strength_label->setString(strength2);                //显示角色体力

	this->addChild(player2);
	players_vector.pushBack(player2);
}

void GameBaseLayer::addGoButton()
{
	//GO按钮
	goMenuItem = MenuItemImage::create(GO_BUTTON_NORMAL,GO_BUTTON_SELECTED,CC_CALLBACK_1(GameBaseLayer::goButtomCallback,this));
	goMenuItem->setPosition(Vec2(tableStartPosition_x + 1.5*tableWidth,tableStartPosition_y - tableHeight * 6.5));
	goMenuItem->setScale(0.8);
	goMenuItem->setTag(GO_MENU_ITEM_TAG);
	goMenuItem->setAnchorPoint(Vec2(0.5,0.5));

	//技能按钮
	skillMenuItem = MenuItemImage::create("images/skill_button_normal.png","images/skill_button_pressed.png",CC_CALLBACK_1(GameBaseLayer::goButtomCallback,this));
	skillMenuItem->setPosition(Vec2(tableStartPosition_x + 1.5*tableWidth,tableStartPosition_y - tableHeight * 7 - goMenuItem->getContentSize().height/2 ));
	skillMenuItem->setScale(0.8);
	skillMenuItem->setTag(SKILL_MENU_ITEM_TAG);
	skillMenuItem->setAnchorPoint(Vec2(0.5,0.5));

	menu = Menu::create(goMenuItem,skillMenuItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,1,MENU_TAG);
	
	//暴风骤雨技能显示界面 
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
	
	//巧取豪夺显示界面  
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

	//添加各个技能界面点击回调方法  
	skillStorm->setSkillButtonCallback(this,callfuncN_selector(GameBaseLayer::skillStormCallback));
	skillTransfer->setSkillButtonCallback(this,callfuncN_selector(GameBaseLayer::skillTransferCallback));

	//技能界面是否在显示  
	isShowSkillLayer = false;
	
}




void GameBaseLayer::setWayPassToGrid()
{
	wayLayer = _map->getLayer("way");   //获取地图way层
	Size _mapSize = wayLayer->getLayerSize();
	//根据way图层，获取道路的坐标，并转换成行列值，在canPassGrid相对应的位置设置true，来记录可以通过的道路
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
				wayLayerPass_Vector.push_back(p);   //将坐标保存到容器中  
				log("canPassGrid row=  %d ,col =%d ,canpass = %d" ,row,col,canPassGrid[row][col]);
			}

		}
	}
	log("setWayPassToGrid finished");

}


void GameBaseLayer::goButtomCallback(Ref *pSender)
{	
	//音效
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
			showSkillSprites();   //隐藏技能界面函数
		}		
	}
	else if(menuItem->getTag() == SKILL_MENU_ITEM_TAG)
	{
		//设置消耗的体力
		skillStorm->setStrength(50);
		skillTransfer->setStrength(100);
				
		showSkillSprites();   //显示/隐藏技能界面
	}
	
}

void GameBaseLayer::showSkillSprites()     //显示/隐藏技能界面函数
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
	if(player1->getStop_x()<0)    //判断停留位置是否是初始状态
	{
		return;
	}
	if(player1->getStrength()>=50)   //判断当前体力是否大于等于技能所需体力
	{
		int landTag = landLayer->getTileGIDAt(Vec2(player1->getStop_x(),player1->getStop_y()));
		if(landTag != player1_building_1_tiledID && landTag != player1_building_2_tiledID && landTag != player1_building_3_tiledID)
		{
			//音效
			if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
			{
				SimpleAudioEngine::getInstance()->playEffect(STORM_EFFECT);
				int rand1 = rand()%(player1EffectVec_4.size());
				SimpleAudioEngine::getInstance()->playEffect(player1EffectVec_4.at(rand1)->getCString());
				nextPlayerEffectVec = player2EffectVec_5;
				this->scheduleOnce(schedule_selector(GameBaseLayer::playNextEffectVec),2.0f);
			}
			goMenuItem->setEnabled(false);   //技能释放过程中，不允许行走，会影响技能判断当前位置

			showSkillSprites();  //隐藏界面 
			refreshStrength(player1,-50);             //扣除消耗的体力
			Vec2 pointOfGL = Util::map2GL(Vec2(player1->getStop_x(),player1->getStop_y()),GameBaseLayer::_map);   

			auto rainSprite = Sprite::createWithSpriteFrame(player1->getRain_skill_animate()->getAnimation()->getFrames().at(0)->getSpriteFrame());					
			rainSprite->setAnchorPoint(Vec2(0,0));
			rainSprite->setPosition(pointOfGL + Vec2(-tiledWidth/2,tiledHeight/2));
			this->addChild(rainSprite);

			rainSprite->runAction(Sequence::create(
				player1->getRain_skill_animate(),              //播放动画
				CallFunc::create([this,rainSprite]()
				{
					landLayer->setTileGID(blank_land_tiledID,Vec2(player1->getStop_x(),player1->getStop_y()));  //将土地变成空地
					rainSprite->removeFromParent();   //移除
					goMenuItem->setEnabled(true);   //技能释放完毕，允许行走 
				}),
				NULL));		
		}		
	}
	else   //如果体力不足，则提示
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
	if(player1->getStop_x()<0)    //判断停留位置是否是初始状态
	{
		return;
	}	
	
	if(player1->getStrength()>=100)   //判断当前体力是否大于等于技能所需体力
	{
		//获取土地的tiledID
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
			//音效
			if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
			{
				int rand1 = rand()%(player1EffectVec_2.size());
				SimpleAudioEngine::getInstance()->playEffect(player1EffectVec_2.at(rand1)->getCString());
				nextPlayerEffectVec = player2EffectVec_3;
				this->scheduleOnce(schedule_selector(GameBaseLayer::playNextEffectVec),2.0f);
			}
			goMenuItem->setEnabled(false);   //技能释放过程中，不允许行走，会影响技能判断当前位置

			showSkillSprites();  //隐藏界面 
			refreshStrength(player1,-100);             //扣除消耗的体力
			Vec2 pointOfGL = Util::map2GL(Vec2(player1->getStop_x(),player1->getStop_y()),GameBaseLayer::_map);   

			auto transferSprite = Sprite::createWithSpriteFrame(player1->getTransfer_skill_animate()->getAnimation()->getFrames().at(0)->getSpriteFrame());					
			transferSprite->setAnchorPoint(Vec2(0,0));
			transferSprite->setPosition(pointOfGL);
			this->addChild(transferSprite);

			transferSprite->runAction(Sequence::create(
				player1->getTransfer_skill_animate(),              //播放动画
				CallFunc::create([this,transferSprite,transferLand]()
				{
					landLayer->setTileGID(transferLand,Vec2(player1->getStop_x(),player1->getStop_y()));  //将土地变成自己的
					transferSprite->removeFromParent();   //移除
					goMenuItem->setEnabled(true);   //技能释放完毕，允许行走 
				}),
				NULL));			
		}		
	}
	else   //如果体力不足，则提示
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
	//监听MSG_GO消息，让go键出现/隐藏
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseLayer::receiveNotificationOMsg),
		MSG_GO,
		NULL);

	//监听MSG_BUY消息，处理购买土地事件
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseLayer::receiveNotificationOMsg),
		MSG_BUY,
		NULL);

	//监听MSG_PAY_TOLLS消息，处理缴纳过路费事件
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseLayer::receiveNotificationOMsg),
		MSG_PAY_TOLLS,
		NULL);

	//监听MSG_RANDOM_ASK_EVENT消息，处理问号随机事件
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseLayer::receiveNotificationOMsg),
		MSG_RANDOM_ASK_EVENT,
		NULL);
	
	//监听MSG_STRENGTH_UP消息，处理捡到体力的事件
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseLayer::receiveNotificationOMsg),
		MSG_STRENGTH_UP,
		NULL);

	//监听MSG_USE_SKILL消息，处理敌方角色使用技能事件
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseLayer::receiveNotificationOMsg),
		MSG_USE_SKILL,
		NULL);

	//监听游戏结束消息
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
		if(messageVector.at(3)->intValue() == PLAYER_1_TAG)    //角色1
		{
			//记录角色最后停留位置的四周的土地位置
			player1->setStop_x(messageVector.at(1)->intValue());
			player1->setStop_y(messageVector.at(2)->intValue());
		}
		if(messageVector.at(3)->intValue() == PLAYER_2_TAG)    //角色2
		{
			//记录角色最后停留位置的四周的土地位置
			player2->setStop_x(messageVector.at(1)->intValue());
			player2->setStop_y(messageVector.at(2)->intValue());
		}
	}
		
	switch(retMsgType)
	{
	case MSG_GO_SHOW_TAG:              //当收到的消息是MSG_GO_SHOW_TAG时，表示要显示goMenuItem项
		{
			for(int i =0;i<menu.size();i++)
			{	
				Node* node = menu.at(i);
				node->runAction(MoveBy::create(0.3f,Vec2(-(node->getContentSize().width)*2,0)));
				diceSprite->resume();      //骰子恢复摇动
				gameRoundCount++;          //步数+1
				refresshRoundDisplay();    //更新步数

				goMenuItem->setEnabled(true);    //go按钮可以按
			}
			break;
		}		
	case MSG_GO_HIDE_TAG:      //当收到的消息是MSG_GO_HIDE_TAG时，表示要隐藏goMenuItem项
		{
			for(int i =0;i<menu.size();i++)
			{
				goMenuItem->setEnabled(false);     //go按钮不可以按

				Node* node = menu.at(i);
				node->runAction(MoveBy::create(0.3f,Vec2(node->getContentSize().width*2,0)));
			}
			//设置骰子
			__String *frameName = __String::createWithFormat("dice_%02d.png",randNumber);
			diceSprite->setSpriteFrame(diceFrameCache->getSpriteFrameByName(frameName->getCString()));
				
			diceSprite->pause();    //动作暂停
			break;
		}
	case MSG_BUY_BLANK_TAG:    //当收到的消息是MSG_BUY_BLANK_TAG时，表示要购买空地
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerType = messageVector.at(3)->intValue();

			//根据角色分别处理购买土地事件
			switch(playerType)
			{
			case PLAYER_1_TAG:      
				showBuyLandDialog(MSG_BUY_BLANK_TAG);  //如果是角色1 ，则弹出对话框
				transferLandTag = 0;
				break;
			case PLAYER_2_TAG:     //如果是角色2，则直接够买，并播放购买动画
				{
					//音效
					if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
					{
						int rand1 = rand()%(player2EffectVec_8.size());
						SimpleAudioEngine::getInstance()->playEffect(player2EffectVec_8.at(rand1)->getCString());
					}
					buyLand(MSG_BUY_BLANK_TAG,buy_land_x,buy_land_y,foot2Sprite,player2_building_1_tiledID,player2,PLAYER2_1_PARTICLE_PLIST);
					NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));  //当该角色操作完时，发送信息，让下一个角色行动
					break;
				}				
			}	
			break;
		}
	case MSG_BUY_LAND_1_TAG:         //升级地图，脚印变为海星，
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerType = messageVector.at(3)->intValue();

			//根据角色分别处理购买土地事件
			switch(playerType)
			{
			case PLAYER_1_TAG:     
				showBuyLandDialog(MSG_BUY_LAND_1_TAG);  //如果是角色1 ，则弹出对话框

				transferLandTag = 0;
				break;
			case PLAYER_2_TAG:     //如果是角色2，则直接够买，并播放购买动画
				{
					//音效
					if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
					{
						int rand1 = rand()%(player2EffectVec_7.size());
						SimpleAudioEngine::getInstance()->playEffect(player2EffectVec_7.at(rand1)->getCString());
					}
					//升级土地
					buyLand(MSG_BUY_LAND_1_TAG,buy_land_x,buy_land_y,star2Sprite,player2_building_2_tiledID,player2,PLAYER2_1_PARTICLE_PLIST);
					NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));  //当该角色操作完时，发送信息，让下一个角色行动
					break;
				}
			}
			break;
		}
	case MSG_BUY_LAND_2_TAG:         //升级地图，海星变为心形
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerType = messageVector.at(3)->intValue();

			//根据角色分别处理购买土地事件
			switch(playerType)
			{
			case PLAYER_1_TAG:      
				showBuyLandDialog(MSG_BUY_LAND_2_TAG);  //如果是角色1 ，则弹出对话框

				transferLandTag = 0;
				break;
			case PLAYER_2_TAG:     //如果是角色2，则直接够买，并播放购买动画
				{
					//音效
					if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
					{
						int rand1 = rand()%(player2EffectVec_7.size());
						SimpleAudioEngine::getInstance()->playEffect(player2EffectVec_7.at(rand1)->getCString());
					}
					//升级土地
					buyLand(MSG_BUY_LAND_2_TAG,buy_land_x,buy_land_y,heart2Sprite,player2_building_3_tiledID,player2,PLAYER2_1_PARTICLE_PLIST);
					NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));  //当该角色操作完时，发送信息，让下一个角色行动
					break;
				}
			}
			break;
		}
	case MSG_PAY_TOLLS_1_TAG:     //缴纳1级土地过路费
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerType = messageVector.at(3)->intValue();
			payTolls(MSG_PAY_TOLLS_1_TAG,buy_land_x,buy_land_y,playerType);
			break;
		}
	case MSG_PAY_TOLLS_2_TAG:     //缴纳2级土地过路费
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerType = messageVector.at(3)->intValue();
			payTolls(MSG_PAY_TOLLS_2_TAG,buy_land_x,buy_land_y,playerType);
			break;
		}
	case MSG_PAY_TOLLS_3_TAG:    //缴纳3级土地过路费
		{
			buy_land_x = messageVector.at(1)->floatValue();
			buy_land_y = messageVector.at(2)->floatValue();
			int playerType = messageVector.at(3)->intValue();
			payTolls(MSG_PAY_TOLLS_3_TAG,buy_land_x,buy_land_y,playerType);
			break;
		}
	case  MSG_RANDOM_ASK_EVENT_TAG:  //问号随机事件
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
	case MSG_STRENGTH_UP30_TAG:     //捡到积分卡，恢复30体力
		{
			int playerTag = messageVector.at(3)->intValue();
			doStrengthUpEvent(MSG_STRENGTH_UP30_TAG,playerTag);
			this->scheduleOnce(schedule_selector(GameBaseLayer::sendMSGDealLandRound),TOAST_SHOW_TIME);
			break;
		}

	case MSG_STRENGTH_UP50_TAG:     //捡到积分卡，恢复50体力
		{
			int playerTag = messageVector.at(3)->intValue();
			doStrengthUpEvent(MSG_STRENGTH_UP50_TAG,playerTag);   //处理
			this->scheduleOnce(schedule_selector(GameBaseLayer::sendMSGDealLandRound),TOAST_SHOW_TIME);
			break;
		}

	case MSG_STRENGTH_UP80_TAG:     //捡到积分卡，恢复80体力
		{
			int playerTag = messageVector.at(3)->intValue();
			doStrengthUpEvent(MSG_STRENGTH_UP80_TAG,playerTag);    //处理
			this->scheduleOnce(schedule_selector(GameBaseLayer::sendMSGDealLandRound),TOAST_SHOW_TIME);
			break;
		}

	case MSG_USE_SKILL_TAG:   //敌方角色使用技能
		{
			//获取角色的tag   
            int playerTag = messageVector.at(3)->intValue();  
            //角色要使用的技能  
            int kill_index =  messageVector.at(4)->intValue();  
            //使用技能需要耗费的体力  
            int needLostStrength = messageVector.at(5)->intValue();  
            //当前地块的等级  
            int landLevel = messageVector.at(6)->intValue();  

			if(playerTag == PLAYER_2_TAG)  
            {  
                //让角色减少相应的体力    
				refreshStrength(player2,-needLostStrength);  
				Vec2 pointOfGL = Util::map2GL(Vec2(player2->getStop_x(),player2->getStop_y()),_map);  
                //播放技能相应动画  
                switch(kill_index)  
                {  
                case 0://暴风骤雨  
					{ 
						//音效
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
                        
                        //动画播放,完毕后，设置地块为空地块。并发送角色继续行走的消息  
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
                case 1://巧取豪夺  
                    {  
						//音效
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
                                       
                        //动画播放完毕后，设置地块为自己相应等级地块。并发送角色继续行走的消息  
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
			if(playerType == PLAYER_1_TAG)   //如果是角色1，则输了
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
				//播放粒子效果
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
	NotificationCenter::getInstance()->postNotification(MSG_AROUND_LAND,__String::createWithFormat("%d",MSG_AROUND_LAND_TAG));  //发送信息，处理购买土地或缴费	
}

void GameBaseLayer::sendMSGPickOneToGO(float dt)
{
	NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,__String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));  //发送信息，让下一个角色行动
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

//处理捡到积分卡，体力回升事件
void GameBaseLayer::doStrengthUpEvent(int strengthUp,int playerTag)
{
	//音效
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
			strengthUpSprite->runAction(action);     //播放体力回升动画
			//提示信息
			CocosToast::createToast(
				this,
				__String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(STRENGTH_UP)->getCString(),strengthValue)->getCString(),
				TOAST_SHOW_TIME,
				player1->getPosition());     

			refreshStrength(player1,strengthValue);       //更新体力显示
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
			strengthUpSprite->runAction(action);     //播放体力回升动画

			//提示信息
			CocosToast::createToast(
				this,
				__String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(STRENGTH_UP)->getCString(),strengthValue)->getCString(),
				TOAST_SHOW_TIME,
				player2->getPosition());     

			refreshStrength(player2,strengthValue);       //更新体力显示
			break;
		}
	}
}

void GameBaseLayer::doRandomAskEvent(RicherPlayer *player)
{
	int randomNumber = rand()%(randomAskEventMap.size()) + 1;  //随机一个数字（1~Map的容量）

	switch(randomNumber)
	{
	case TAX_REBATES_TAG:
		refreshMoney(player,10000);       //政府鼓励投资，返还税金10000
		break;
	case PAY_TAXES_TAG:
		{
			//音效
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
			refreshMoney(player,-20000);      //政府严查账务，补交税金20000
			break;
		}
	case LOSS_STRENGTH_TAG:
		refreshStrength(player,-100);     //喝到假酒，上吐下泻，体力耗光
		break;
	case PHYSICAL_RECOVERY_TAG:
		refreshStrength(player,+100);     //吃了大补丸，体力恢复
		break;
	case INVESTMENT_DIVIDENDS_TAG:
		refreshMoney(player,20000);       //投资获利，分红20000
		break;
	case INVESTMENT_LOSS_TAG:
		refreshMoney(player,-30000);      //投资失败，亏损30000
		break;
	}

	__String *str = randomAskEventMap.at(randomNumber);
	CocosToast::createToast(
		this,
		LanguageString::getInstance()->getLanguageString(str->getCString())->getCString(),
		TOAST_SHOW_TIME,
		player->getPosition());    //Toast提示事件信息
}

void GameBaseLayer::buyLand(int buyTag,float x,float y,Sprite *landSprite,int landLevel,RicherPlayer *player,char *particlelistName)
{
	int money = 0;
	//判断购买土地需要多少钱
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
	//判断缴纳过路费的级别
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

	if(playerTag ==PLAYER_1_TAG)    //如果是角色1缴纳的话，就角色1扣钱，土地所有者加钱
	{
		//音效
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
	else if(playerTag ==PLAYER_2_TAG)   //如果是角色2缴纳的话，就角色1扣钱，土地所有者加钱
	{
		//音效
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
	if(gid == player1_building_1_tiledID || gid == player1_building_2_tiledID || gid == player1_building_3_tiledID)    //判断是不是角色1的土地
	{
		return player1;
	}

	if(gid == player2_building_1_tiledID || gid == player2_building_2_tiledID || gid == player2_building_3_tiledID)     //判断是不是角色2的土地
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

	//游戏开始时，回合为0
	if(count == 0)
	{
		st = Sprite::createWithSpriteFrame(digitalRoundVector.at(0));		
		this->addChild(st);
		refreshRoundVector.pushBack(st);
	}
	//将回合数转换成sprite，存放都容器中
	while(count>0)
	{
		st = Sprite::createWithSpriteFrame(digitalRoundVector.at(count%10));     //先从个位数开始存
		refreshRoundVector.pushBack(st);
		this->addChild(st);
		count = count/10;
	}

	refreshRoundVector.reverse();   //因为存放时都是倒序存放的，现在要将顺序倒回来

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
			//音效
			if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
			{
				int rand1 = rand()%(player1EffectVec_8.size());
				SimpleAudioEngine::getInstance()->playEffect(player1EffectVec_8.at(rand1)->getCString());
			}
			buyLand(MSG_BUY_BLANK_TAG,buy_land_x,buy_land_y,foot1Sprite,player1_building_1_tiledID,player1,PLAYER1_1_PARTICLE_PLIST);				
			break;			
		case MSG_BUY_LAND_1_TAG:
			//音效
			if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
			{
				int rand1 = rand()%(player1EffectVec_7.size());
				SimpleAudioEngine::getInstance()->playEffect(player1EffectVec_7.at(rand1)->getCString());
			}
			buyLand(MSG_BUY_LAND_1_TAG,buy_land_x,buy_land_y,star1Sprite,player1_building_2_tiledID,player1,PLAYER1_1_PARTICLE_PLIST);
			break;
		case MSG_BUY_LAND_2_TAG:
			//音效
			if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
			{
				int rand1 = rand()%(player1EffectVec_7.size());
				SimpleAudioEngine::getInstance()->playEffect(player1EffectVec_7.at(rand1)->getCString());
			}
			buyLand(MSG_BUY_LAND_2_TAG,buy_land_x,buy_land_y,heart1Sprite,player1_building_3_tiledID,player1,PLAYER1_1_PARTICLE_PLIST);
			break;	
		}
		//购买完毕后，让对话框消失，并发送消息，让其他角色行走  
		popDialog->removeFromParent();		
		this->scheduleOnce(schedule_selector(GameBaseLayer::sendMSGPickOneToGO),1.0f);
	}
	else
	{
		//点击取消，让对话框消失，并发送消息，让其他角色行走  
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
		//购买空地，显示的信息
		showContentText = __String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(BUY_LAND_MSG)->getCString(),LAND_BLANK_MONEY);
		break;
	case MSG_BUY_LAND_1_TAG:
		//升级土地，显示的信息
		showContentText = __String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(BUY_LAND_MSG)->getCString(),LAND_LEVEL_1_MONEY);
		break;
	case MSG_BUY_LAND_2_TAG:
		//升级土地，显示的信息
		showContentText = __String::createWithFormat("%s %d",LanguageString::getInstance()->getLanguageString(BUY_LAND_MSG)->getCString(),LAND_LEVEL_2_MONEY);
		break;
	}
	popDialog->getLabelContentText()->setString(showContentText->getCString());
	popDialog->setDataTag(landTag);
	
}

//添加骰子
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
	Vector<SpriteFrame*> strengthUpSprite_vector;      //存放体力回升精灵的容器

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
	//1级土地--脚印的动作

	scaleBy1ForBuyLand = ScaleBy::create(0.1,1.5);    //放大
	scaleBy2ForBuyLand = ScaleBy::create(0.5,0.7);    //缩小
	scaleBy1ForBuyLand->retain();
	scaleBy2ForBuyLand->retain();

	foot1Sprite = Sprite::create(PLAYER1_1_PARTICLE_PNG);    //脚印精灵
	foot1Sprite->setAnchorPoint(Vec2(0,0));
	this->addChild(foot1Sprite);

	foot2Sprite = Sprite::create(PLAYER2_1_PARTICLE_PNG);
	foot2Sprite->setAnchorPoint(Vec2(0,0));
	this->addChild(foot2Sprite);

	//2级土地--海星的动作
	landFadeOut = FadeOut::create(0.1);    //淡出
	landFadeIn = FadeIn::create(0.1);      //淡入
	landFadeIn->retain();
	landFadeOut->retain();

	star1Sprite = Sprite::create(PLAYER1_2_PARTICLE_PNG);
	star1Sprite->setAnchorPoint(Vec2(0,0));
	this->addChild(star1Sprite);

	star2Sprite = Sprite::create(PLAYER2_2_PARTICLE_PNG);
	star2Sprite->setAnchorPoint(Vec2(0,0));
	this->addChild(star2Sprite);

	//3级土地--心形的动作
	heart1Sprite = Sprite::create(PLAYER1_3_PARTICLE_PNG);
	heart1Sprite->setAnchorPoint(Vec2(0,0));
	this->addChild(heart1Sprite);

	heart2Sprite = Sprite::create(PLAYER2_3_PARTICLE_PNG);
	heart2Sprite->setAnchorPoint(Vec2(0,0));
	this->addChild(heart2Sprite);
}

void GameBaseLayer::playParticle(cocos2d::Vec2 point,char *plistName)
{
	//粒子效果
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
	//交过路费声音0-6
	player2EffectVec_1.pushBack(String::create(P2_SPEAKING01));
	player2EffectVec_1.pushBack(String::create(P2_QISIWOLE));
	player2EffectVec_1.pushBack(String::create(P2_XINHAOKONGA));
	player2EffectVec_1.pushBack(String::create(P2_BUHUIBA));
	player2EffectVec_1.pushBack(String::create(P2_PAYHIGH));
	player2EffectVec_1.pushBack(String::create(P2_QIANGQIANA));
	player2EffectVec_1.pushBack(String::create(P2_HEBAOCHUXIE));

	//抢夺别人地块7-10
	player2EffectVec_2.pushBack(String::create(P2_BIEGUAIWO));
	player2EffectVec_2.pushBack(String::create(P2_SPEAKING02));
	player2EffectVec_2.pushBack(String::create(P2_TIGER));
	player2EffectVec_2.pushBack(String::create(P2_NIDEJIUSHODE));
	
	//房屋被抢夺11-14
	player2EffectVec_3.pushBack(String::create(P2_ZHENMIANMU));
	player2EffectVec_3.pushBack(String::create(P2_WODEDIQI));
	player2EffectVec_3.pushBack(String::create(P2_HAOQIFU));
	player2EffectVec_3.pushBack(String::create(P2_WANGFA));

	//摧毁别人房屋15-18
	player2EffectVec_4.pushBack(String::create(P2_NIGAIWOCHAI));
	player2EffectVec_4.pushBack(String::create(P2_KANWODE));
	player2EffectVec_4.pushBack(String::create(P2_HAIRENLE));
	player2EffectVec_4.pushBack(String::create(P2_BAOCHOU));
	
	//房屋被摧毁19-22
	player2EffectVec_5.pushBack(String::create(P2_WODEYANGFANG));
	player2EffectVec_5.pushBack(String::create(P2_QIFURENJIA));
	player2EffectVec_5.pushBack(String::create(P2_SHAQIANDAO));
	player2EffectVec_5.pushBack(String::create(P2_LIANXIANGXIYU));
	player2EffectVec_5.pushBack(String::create(P2_HAOJIUGAIHAO));

	//收取过路费23 - 28
	player2EffectVec_6.pushBack(String::create(P2_RENBUWEIJI));
	player2EffectVec_6.pushBack(String::create(P2_XIAOQI));
	player2EffectVec_6.pushBack(String::create(P2_RONGXING));
	player2EffectVec_6.pushBack(String::create(P2_MANYI));
	player2EffectVec_6.pushBack(String::create(P2_XIAOFUPO));
	player2EffectVec_6.pushBack(String::create(P2_DUOGEI));

	//升级房子29-30
	player2EffectVec_7.pushBack(String::create(P2_HIGHER));
	player2EffectVec_7.pushBack(String::create(P2_WANZHANGGAOLOU));

	//买地31 - 34
	player2EffectVec_8.pushBack(String::create(P2_BUYIT));
	player2EffectVec_8.pushBack(String::create(P2_HAODEKAISHI));
	player2EffectVec_8.pushBack(String::create(P2_RANGNIZHU));
	player2EffectVec_8.pushBack(String::create(P2_MAIWOBA));

	//对方被罚收税35-38
	player2EffectVec_9.pushBack(String::create(P2_TOUSHUI));
	player2EffectVec_9.pushBack(String::create(P2_FALVZHICAI));
	player2EffectVec_9.pushBack(String::create(P2_GUOKU));
	player2EffectVec_9.pushBack(String::create(P2_NASHUI));



	//交过路费声音
	player1EffectVec_1.pushBack(String::create(P1_Speaking_00435));
	player1EffectVec_1.pushBack(String::create(P1_Speaking_00461));
	player1EffectVec_1.pushBack(String::create(P1_Speaking_00475));
	player1EffectVec_1.pushBack(String::create(P1_Speaking_01060));
	player1EffectVec_1.pushBack(String::create(P1_Speaking_01062));

	//抢夺别人地块
	player1EffectVec_2.pushBack(String::create(P1_Speaking_00429));

	//房屋被抢夺
	player1EffectVec_3.pushBack(String::create(P1_Speaking_00430));
	player1EffectVec_3.pushBack(String::create(P1_Speaking_00464));
	player1EffectVec_3.pushBack(String::create(P1_Speaking_00469));
	player1EffectVec_3.pushBack(String::create(P1_Speaking_00470));
	player1EffectVec_3.pushBack(String::create(P1_Speaking_00476));

	//摧毁别人房屋
	player1EffectVec_4.pushBack(String::create(P1_Speaking_00433));
	player1EffectVec_4.pushBack(String::create(P1_Speaking_00437));

	//房屋被摧毁
	player1EffectVec_5.pushBack(String::create(P1_Speaking_00462));
	player1EffectVec_5.pushBack(String::create(P1_Speaking_00463));
	player1EffectVec_5.pushBack(String::create(P1_Speaking_00466));
	player1EffectVec_5.pushBack(String::create(P1_Speaking_00468));
	player1EffectVec_5.pushBack(String::create(P1_Speaking_00474));
	player1EffectVec_5.pushBack(String::create(P1_Speaking_01061));

	//收取过路费
	player1EffectVec_6.pushBack(String::create(P1_Speaking_00453));
	player1EffectVec_6.pushBack(String::create(P1_Speaking_01059));
	player1EffectVec_6.pushBack(String::create(P1_Speaking_01057));
	//升级房子
	player1EffectVec_7.pushBack(String::create(P1_Speaking_01051));
	player1EffectVec_7.pushBack(String::create(P1_Speaking_01066));

	//买地
	player1EffectVec_8.pushBack(String::create(P1_Speaking_00458));
	player1EffectVec_8.pushBack(String::create(P1_Speaking_01067));

	//对方被罚收税
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
