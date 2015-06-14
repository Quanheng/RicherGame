#include "RicherGameController.h"
#include "GameBaseScene.h"
#include "RouteNavigation.h"

USING_NS_CC;

RicherGameController* RicherGameController::rgContreoller_Instance = NULL;

RicherGameController::RicherGameController()
{
	rgContreoller_Instance =NULL;	
	callEndFunc = CallFunc::create(CC_CALLBACK_0(RicherGameController::endMove,this));
	addNotificationObserver();	
}

RicherGameController::~RicherGameController()
{
	spawnAction->release();
}

RicherGameController* RicherGameController::getInstance()
{
	if(!rgContreoller_Instance)
	{
		rgContreoller_Instance = new RicherGameController();
	}
	return rgContreoller_Instance;
}

bool RicherGameController::init()
{
	if(!Layer::init())
	{
		return false;
	}	

	return true;
}

void RicherGameController::startRealGo(std::vector<int> rowVector,std::vector<int> colVector,RicherPlayer *player)
{
	//初始化数据
	_rowVector = rowVector;
	_colVector = colVector;
	currentRow = _rowVector[0];
	currentCol = _colVector[0];
	log("currentRow is %d, currentCol is %d",currentRow,currentCol);
	nextCol = 0;
	nextRow = 0;
	stepHasGone = 0;                  
	stepCount = rowVector.size()- 1;  //根据路径容器的大小，确定要走的步数，因为第一个记录的是当前位置，所以要减1
	richerplayer = player;
	oneRoundDone = false;
	moveOneStep(richerplayer);
	
}

void RicherGameController::moveOneStep(RicherPlayer *player)
{
	//音效
	if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(WALK_MP3);				
	}
				
	nextRow = _rowVector[stepHasGone + 1];
	nextCol = _colVector[stepHasGone + 1];

	int dirctionRow;
	int dirctionCol ;
	dirctionRow = nextRow - currentRow;     //判断下一步的方向，大于0是Up；小于0是Down
	dirctionCol = nextCol - currentCol;     //同上，大于0是Right，小于0是Left
	if(dirctionRow>0)  //Up
	{
		moveBy = MoveBy::create(playerGoTotalTime,Vec2(0,tiledHeight));		
		repeat = Repeat::create(player->getUp(),1);
	}
	else if(dirctionRow<0)  //Down
	{
		moveBy = MoveBy::create(playerGoTotalTime,Vec2(0,-tiledHeight));
		repeat = Repeat::create(player->getDown(),1);
	}
	else if(dirctionCol>0)  //Right
	{
		moveBy = MoveBy::create(playerGoTotalTime,Vec2(tiledWidth,0));
		repeat = Repeat::create(player->getRight(),1);
	}
	else if(dirctionCol<0)  //Left
	{
		moveBy = MoveBy::create(playerGoTotalTime,Vec2(-tiledHeight,0));
		repeat = Repeat::create(player->getLeft(),1);
	}
	spawnAction = Sequence::create(Spawn::create(moveBy,repeat,NULL),callEndFunc,NULL);
	spawnAction->retain();
	player->runAction(spawnAction);	
}

void RicherGameController::endMove()
{
	GameBaseLayer::pathMarkVector.at(stepHasGone)->setVisible(false);;
	stepHasGone++;
	if(stepHasGone>=stepCount)
	{
		richerplayer->setIsMyTurn(false);
		handlePropEvent();
		return;	
	}
	currentCol = nextCol;
	currentRow = nextRow;
	moveOneStep(richerplayer);	
}

void RicherGameController::pickOnePlayerToGo()
{
	for(int i =0; i < GameBaseLayer::players_vector.size();i++)
	{
		RicherPlayer *player = GameBaseLayer::players_vector.at(i);

		//判断游戏是否结束
		if(player->getMoney()<=0)
		{
			String * str = String::createWithFormat("%d-%f-%f-%d",MSG_GAME_OVER_TAG,0.0f,0.0f,player->getTag());  
            NotificationCenter::getInstance()->postNotification(MSG_GAME_OVER,str);  
            return;//游戏返回，不再向下执行  			
		}

		if(player->getIsMyTurn())
		{
			////////////////////////敌方角色使用技能start//////////////////
			if(player->getStop_x() > 0)  
			{  
				//获取角色所在地块id值  
				int gid = GameBaseLayer::landLayer->getTileGIDAt(Vec2(player->getStop_x(),player->getStop_y()));  
				//如果地块不是自己的，则随机使用技能  
				if(gid != GameBaseLayer::blank_land_tiledID && gid != GameBaseLayer::player2_building_1_tiledID && 
					gid != GameBaseLayer::player2_building_2_tiledID && gid != GameBaseLayer::player2_building_3_tiledID)  
				{   
					//获取角色体力  
					int playerStrength = player->getStrength();  
					//随机取得要使用的技能  
					int randomSkill_index = rand()%2;  
					int needLostStrength = 0;  
					int landLevel = 0;  
					//记录地块的等级  
					if(gid == GameBaseLayer::player1_building_1_tiledID)  
					{  
						landLevel =  GameBaseLayer::player2_building_1_tiledID;  
					}  
					if(gid == GameBaseLayer::player1_building_2_tiledID)  
					{  
						landLevel =  GameBaseLayer::player2_building_2_tiledID;  
					}  
					if(gid == GameBaseLayer::player1_building_3_tiledID)  
					{  
						landLevel =  GameBaseLayer::player2_building_3_tiledID;  
					}  

					//获取使用技能需要耗费的体力  
					switch(randomSkill_index)  
					{  
					case 0:  //代表暴风骤雨技能
						{  
							needLostStrength = 50;  
							break;  
						}  
					case 1:  //代表巧取豪夺技能
						{  
							needLostStrength = 100;  
							break;
						}  					
					}  
					//如果角色体力值满足要求，发送使用技能的消息，然后方法返回  
					if(playerStrength >= needLostStrength)  
					{  
						__String *str = __String::createWithFormat("%d-%d-%d-%d-%d-%d-%d",MSG_USE_SKILL_TAG,player->getStop_x() ,player->getStop_y(),player->getTag(),randomSkill_index,needLostStrength,landLevel);  
						NotificationCenter::getInstance()->postNotification(MSG_USE_SKILL,str);  
						return;  
					}     
				}     
			}  			
			////////////////////////////////技能使用end///////////////////////

			int num = rand()%6 + 1;
			RouteNavigation::getInstance()->getPath(player,num,GameBaseLayer::canPassGrid,GameBaseLayer::tiledRowsCount,GameBaseLayer::tiledColsCount);
			std::vector<int> rowVector = RouteNavigation::getInstance()->getPathRows_vector();
			std::vector<int> colVector = RouteNavigation::getInstance()->getPathCols_vector();
			player->startGo(rowVector,colVector);
			return ;
		}		
	}
	for(int i=0;i<GameBaseLayer::players_vector.size();i++)
	{
		RicherPlayer *player = GameBaseLayer::players_vector.at(i);
		player->setIsMyTurn(true);
	}
	NotificationCenter::getInstance()->postNotification(MSG_GO,__String::createWithFormat("%d",MSG_GO_SHOW_TAG));
}

void RicherGameController::handlePropEvent()
{  
	float playerEnd_x = _colVector[stepCount]*32;       //取得角色当前所在位置的X坐标
	float playerEnd_y = _rowVector[stepCount]*32+32;    //取得角色当前所在位置的y坐标
	Point pointInMap = Util::GL2map(Vec2(playerEnd_x,playerEnd_y),GameBaseLayer::_map);
	
	float x = pointInMap.x;
	float y = pointInMap.y;

	int endId = GameBaseLayer::wayLayer->getTileGIDAt(pointInMap);

	if(endId == GameBaseLayer::randomEvent_tiledID)    //判断该位置是否是问号事件
	{
		__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_RANDOM_ASK_EVENT_TAG,x,y,richerplayer->getTag());
		NotificationCenter::getInstance()->postNotification(MSG_RANDOM_ASK_EVENT,msgStr);    
		return;
	}
	if(endId == GameBaseLayer::strength_30_tiledID)    //判断该位置是否是+30体力
	{
		__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_STRENGTH_UP30_TAG,x,y,richerplayer->getTag());
		NotificationCenter::getInstance()->postNotification(MSG_STRENGTH_UP,msgStr);    
		return;
	}
	if(endId == GameBaseLayer::strength_50_tiledID)    //判断该位置是否是+30体力
	{
		__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_STRENGTH_UP50_TAG,x,y,richerplayer->getTag());
		NotificationCenter::getInstance()->postNotification(MSG_STRENGTH_UP,msgStr);    
		return;
	}
	if(endId == GameBaseLayer::strength_80_tiledID)    //判断该位置是否是+30体力
	{
		__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_STRENGTH_UP80_TAG,x,y,richerplayer->getTag());
		NotificationCenter::getInstance()->postNotification(MSG_STRENGTH_UP,msgStr);    
		return;
	}

	//没有完问号事件和体力事件，则处理土地事件
	handleLandEvent();
}


//处理土地的事件（购买土地、升级土地、缴纳路费）
void RicherGameController::handleLandEvent()
{
	float playerEnd_x = _colVector[stepCount]*32;       //取得角色当前所在位置的X坐标
	float playerEnd_y = _rowVector[stepCount]*32+32;    //取得角色当前所在位置的y坐标

	float **positionAroundEnd;   //定义一个二维数组，存放角色当前位置上下左右四个方向的坐标
	positionAroundEnd = new float *[4];  
	for(int i =0;i<4;i++)
	{
		positionAroundEnd[i] = new float [2];
	}

	//上
	positionAroundEnd[0][0] = playerEnd_x;
	positionAroundEnd[0][1] = playerEnd_y +32;
	//下
	positionAroundEnd[1][0] = playerEnd_x;
	positionAroundEnd[1][1] = playerEnd_y -32;
	//左
	positionAroundEnd[2][0] = playerEnd_x -32;
	positionAroundEnd[2][1] = playerEnd_y;
	//右
	positionAroundEnd[3][0] = playerEnd_x +32;
	positionAroundEnd[3][1] = playerEnd_y;

	//寻找四个相邻位置 
	for(int i = 0; i<4;i++)
	{
		// GL2map是把当前的坐标转换成landLayer层对应的坐标。
		Point ptMap = Util::GL2map(Vec2(positionAroundEnd[i][0],positionAroundEnd[i][1]),GameBaseLayer::_map);
		float x = ptMap.x;
		float y = ptMap.y;
		int titleId = GameBaseLayer::landLayer->getTileGIDAt(ptMap);

		if(titleId == GameBaseLayer::blank_land_tiledID)    //判断空地
		{			
			__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_BUY_BLANK_TAG,x,y,richerplayer->getTag());
			NotificationCenter::getInstance()->postNotification(MSG_BUY,msgStr);  //发送要求买地的消息MSG_BUY，该消息包含了该空地的坐标 、哪个角色，以“-”做为字符串分隔符  
			return;
		}
		if(titleId == GameBaseLayer::player1_building_1_tiledID)   //是否是角色1的等级为1的土地
		{
			if(richerplayer->getTag() == PLAYER_1_TAG)   //如果是角色1
			{
				//发送升级地图消息
				__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_BUY_LAND_1_TAG,x,y,richerplayer->getTag());
				NotificationCenter::getInstance()->postNotification(MSG_BUY,msgStr); 
			}
			else
			{
				//缴纳路费
				__String * str = __String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_1_TAG,x,y,richerplayer->getTag());
                NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);  
			}
			return;
		}
		if(titleId == GameBaseLayer::player1_building_2_tiledID)   //是否是角色1的等级为2的土地
		{
			if(richerplayer->getTag() == PLAYER_1_TAG)   //如果是角色1
			{
				//发送升级地图消息
				__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_BUY_LAND_2_TAG,x,y,richerplayer->getTag());
				NotificationCenter::getInstance()->postNotification(MSG_BUY,msgStr); 
			}
			else
			{
				//缴纳路费
				__String * str = __String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_2_TAG,x,y,richerplayer->getTag());
                NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);  
			}
			return;
		}
		if(titleId == GameBaseLayer::player1_building_3_tiledID)   //是否是角色1的等级为3的土地
		{
			if(richerplayer->getTag() == PLAYER_1_TAG)   //如果是角色1
			{
				//什么都不做，发送消息，让下一个角色行走
				NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,__String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG)); 
			}
			else
			{
				//缴纳路费
				__String * str = __String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_3_TAG,x,y,richerplayer->getTag());
                NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);  
			}
			return;
		}
		if(titleId == GameBaseLayer::player2_building_1_tiledID)   //是否是角色2的等级为1的土地
		{
			if(richerplayer->getTag() == PLAYER_2_TAG)   //如果是角色2
			{
				//发送升级地图消息
				__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_BUY_LAND_1_TAG,x,y,richerplayer->getTag());
				NotificationCenter::getInstance()->postNotification(MSG_BUY,msgStr); 
			}
			else
			{
				//缴纳路费
				__String * str = __String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_1_TAG,x,y,richerplayer->getTag());
                NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);  
			}
			return;
		}
		if(titleId == GameBaseLayer::player2_building_2_tiledID)   //是否是角色2的等级为2的土地
		{
			if(richerplayer->getTag() == PLAYER_2_TAG)   //如果是角色2
			{
				//发送升级地图消息
				__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_BUY_LAND_2_TAG,x,y,richerplayer->getTag());
				NotificationCenter::getInstance()->postNotification(MSG_BUY,msgStr); 
			}
			else
			{
				//缴纳路费
				__String * str = __String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_2_TAG,x,y,richerplayer->getTag());
                NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);  
			}
			return;
		}
		if(titleId == GameBaseLayer::player2_building_3_tiledID)   //是否是角色2的等级为3的土地
		{
			if(richerplayer->getTag() == PLAYER_2_TAG)   //如果是角色2
			{
				//什么都不做，发送消息，让下一个角色行走
				NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,__String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG)); 
			}
			else
			{
				//缴纳路费
				__String * str = __String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_3_TAG,x,y,richerplayer->getTag());
                NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);  
			}
			return;
		}
	}
	//如果角色当前位置上下左右都没有土地，发送消息，则让下一个角色行走
	NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,__String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));
}

void RicherGameController::addNotificationObserver()
{
	//注册监听MSG_PICKONE_TOGO的监听器，处理让下一个角色行走事件
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(RicherGameController::receiveMsg),
		MSG_PICKONE_TOGO,
		NULL);

	//注册监听MSG_RANDOM_ASK_EVENT的监听器,处理问号随机事件
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(RicherGameController::receiveMsg),
		MSG_AROUND_LAND,
		NULL);
}

void RicherGameController::receiveMsg(Ref *pSender)
{
	int msgTag = ((__String*)pSender)->intValue();
	switch(msgTag)
	{
	case MSG_PICKONE_TOGO_TAG:
		pickOnePlayerToGo();
		break;
	case MSG_AROUND_LAND_TAG:
		handleLandEvent();
		break;
	}
}