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
	//��ʼ������
	_rowVector = rowVector;
	_colVector = colVector;
	currentRow = _rowVector[0];
	currentCol = _colVector[0];
	log("currentRow is %d, currentCol is %d",currentRow,currentCol);
	nextCol = 0;
	nextRow = 0;
	stepHasGone = 0;                  
	stepCount = rowVector.size()- 1;  //����·�������Ĵ�С��ȷ��Ҫ�ߵĲ�������Ϊ��һ����¼���ǵ�ǰλ�ã�����Ҫ��1
	richerplayer = player;
	oneRoundDone = false;
	moveOneStep(richerplayer);
	
}

void RicherGameController::moveOneStep(RicherPlayer *player)
{
	//��Ч
	if(UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(WALK_MP3);				
	}
				
	nextRow = _rowVector[stepHasGone + 1];
	nextCol = _colVector[stepHasGone + 1];

	int dirctionRow;
	int dirctionCol ;
	dirctionRow = nextRow - currentRow;     //�ж���һ���ķ��򣬴���0��Up��С��0��Down
	dirctionCol = nextCol - currentCol;     //ͬ�ϣ�����0��Right��С��0��Left
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

		//�ж���Ϸ�Ƿ����
		if(player->getMoney()<=0)
		{
			String * str = String::createWithFormat("%d-%f-%f-%d",MSG_GAME_OVER_TAG,0.0f,0.0f,player->getTag());  
            NotificationCenter::getInstance()->postNotification(MSG_GAME_OVER,str);  
            return;//��Ϸ���أ���������ִ��  			
		}

		if(player->getIsMyTurn())
		{
			////////////////////////�з���ɫʹ�ü���start//////////////////
			if(player->getStop_x() > 0)  
			{  
				//��ȡ��ɫ���ڵؿ�idֵ  
				int gid = GameBaseLayer::landLayer->getTileGIDAt(Vec2(player->getStop_x(),player->getStop_y()));  
				//����ؿ鲻���Լ��ģ������ʹ�ü���  
				if(gid != GameBaseLayer::blank_land_tiledID && gid != GameBaseLayer::player2_building_1_tiledID && 
					gid != GameBaseLayer::player2_building_2_tiledID && gid != GameBaseLayer::player2_building_3_tiledID)  
				{   
					//��ȡ��ɫ����  
					int playerStrength = player->getStrength();  
					//���ȡ��Ҫʹ�õļ���  
					int randomSkill_index = rand()%2;  
					int needLostStrength = 0;  
					int landLevel = 0;  
					//��¼�ؿ�ĵȼ�  
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

					//��ȡʹ�ü�����Ҫ�ķѵ�����  
					switch(randomSkill_index)  
					{  
					case 0:  //���������꼼��
						{  
							needLostStrength = 50;  
							break;  
						}  
					case 1:  //������ȡ���Ἴ��
						{  
							needLostStrength = 100;  
							break;
						}  					
					}  
					//�����ɫ����ֵ����Ҫ�󣬷���ʹ�ü��ܵ���Ϣ��Ȼ�󷽷�����  
					if(playerStrength >= needLostStrength)  
					{  
						__String *str = __String::createWithFormat("%d-%d-%d-%d-%d-%d-%d",MSG_USE_SKILL_TAG,player->getStop_x() ,player->getStop_y(),player->getTag(),randomSkill_index,needLostStrength,landLevel);  
						NotificationCenter::getInstance()->postNotification(MSG_USE_SKILL,str);  
						return;  
					}     
				}     
			}  			
			////////////////////////////////����ʹ��end///////////////////////

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
	float playerEnd_x = _colVector[stepCount]*32;       //ȡ�ý�ɫ��ǰ����λ�õ�X����
	float playerEnd_y = _rowVector[stepCount]*32+32;    //ȡ�ý�ɫ��ǰ����λ�õ�y����
	Point pointInMap = Util::GL2map(Vec2(playerEnd_x,playerEnd_y),GameBaseLayer::_map);
	
	float x = pointInMap.x;
	float y = pointInMap.y;

	int endId = GameBaseLayer::wayLayer->getTileGIDAt(pointInMap);

	if(endId == GameBaseLayer::randomEvent_tiledID)    //�жϸ�λ���Ƿ����ʺ��¼�
	{
		__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_RANDOM_ASK_EVENT_TAG,x,y,richerplayer->getTag());
		NotificationCenter::getInstance()->postNotification(MSG_RANDOM_ASK_EVENT,msgStr);    
		return;
	}
	if(endId == GameBaseLayer::strength_30_tiledID)    //�жϸ�λ���Ƿ���+30����
	{
		__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_STRENGTH_UP30_TAG,x,y,richerplayer->getTag());
		NotificationCenter::getInstance()->postNotification(MSG_STRENGTH_UP,msgStr);    
		return;
	}
	if(endId == GameBaseLayer::strength_50_tiledID)    //�жϸ�λ���Ƿ���+30����
	{
		__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_STRENGTH_UP50_TAG,x,y,richerplayer->getTag());
		NotificationCenter::getInstance()->postNotification(MSG_STRENGTH_UP,msgStr);    
		return;
	}
	if(endId == GameBaseLayer::strength_80_tiledID)    //�жϸ�λ���Ƿ���+30����
	{
		__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_STRENGTH_UP80_TAG,x,y,richerplayer->getTag());
		NotificationCenter::getInstance()->postNotification(MSG_STRENGTH_UP,msgStr);    
		return;
	}

	//û�����ʺ��¼��������¼������������¼�
	handleLandEvent();
}


//�������ص��¼����������ء��������ء�����·�ѣ�
void RicherGameController::handleLandEvent()
{
	float playerEnd_x = _colVector[stepCount]*32;       //ȡ�ý�ɫ��ǰ����λ�õ�X����
	float playerEnd_y = _rowVector[stepCount]*32+32;    //ȡ�ý�ɫ��ǰ����λ�õ�y����

	float **positionAroundEnd;   //����һ����ά���飬��Ž�ɫ��ǰλ�����������ĸ����������
	positionAroundEnd = new float *[4];  
	for(int i =0;i<4;i++)
	{
		positionAroundEnd[i] = new float [2];
	}

	//��
	positionAroundEnd[0][0] = playerEnd_x;
	positionAroundEnd[0][1] = playerEnd_y +32;
	//��
	positionAroundEnd[1][0] = playerEnd_x;
	positionAroundEnd[1][1] = playerEnd_y -32;
	//��
	positionAroundEnd[2][0] = playerEnd_x -32;
	positionAroundEnd[2][1] = playerEnd_y;
	//��
	positionAroundEnd[3][0] = playerEnd_x +32;
	positionAroundEnd[3][1] = playerEnd_y;

	//Ѱ���ĸ�����λ�� 
	for(int i = 0; i<4;i++)
	{
		// GL2map�ǰѵ�ǰ������ת����landLayer���Ӧ�����ꡣ
		Point ptMap = Util::GL2map(Vec2(positionAroundEnd[i][0],positionAroundEnd[i][1]),GameBaseLayer::_map);
		float x = ptMap.x;
		float y = ptMap.y;
		int titleId = GameBaseLayer::landLayer->getTileGIDAt(ptMap);

		if(titleId == GameBaseLayer::blank_land_tiledID)    //�жϿյ�
		{			
			__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_BUY_BLANK_TAG,x,y,richerplayer->getTag());
			NotificationCenter::getInstance()->postNotification(MSG_BUY,msgStr);  //����Ҫ����ص���ϢMSG_BUY������Ϣ�����˸ÿյص����� ���ĸ���ɫ���ԡ�-����Ϊ�ַ����ָ���  
			return;
		}
		if(titleId == GameBaseLayer::player1_building_1_tiledID)   //�Ƿ��ǽ�ɫ1�ĵȼ�Ϊ1������
		{
			if(richerplayer->getTag() == PLAYER_1_TAG)   //����ǽ�ɫ1
			{
				//����������ͼ��Ϣ
				__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_BUY_LAND_1_TAG,x,y,richerplayer->getTag());
				NotificationCenter::getInstance()->postNotification(MSG_BUY,msgStr); 
			}
			else
			{
				//����·��
				__String * str = __String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_1_TAG,x,y,richerplayer->getTag());
                NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);  
			}
			return;
		}
		if(titleId == GameBaseLayer::player1_building_2_tiledID)   //�Ƿ��ǽ�ɫ1�ĵȼ�Ϊ2������
		{
			if(richerplayer->getTag() == PLAYER_1_TAG)   //����ǽ�ɫ1
			{
				//����������ͼ��Ϣ
				__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_BUY_LAND_2_TAG,x,y,richerplayer->getTag());
				NotificationCenter::getInstance()->postNotification(MSG_BUY,msgStr); 
			}
			else
			{
				//����·��
				__String * str = __String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_2_TAG,x,y,richerplayer->getTag());
                NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);  
			}
			return;
		}
		if(titleId == GameBaseLayer::player1_building_3_tiledID)   //�Ƿ��ǽ�ɫ1�ĵȼ�Ϊ3������
		{
			if(richerplayer->getTag() == PLAYER_1_TAG)   //����ǽ�ɫ1
			{
				//ʲô��������������Ϣ������һ����ɫ����
				NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,__String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG)); 
			}
			else
			{
				//����·��
				__String * str = __String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_3_TAG,x,y,richerplayer->getTag());
                NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);  
			}
			return;
		}
		if(titleId == GameBaseLayer::player2_building_1_tiledID)   //�Ƿ��ǽ�ɫ2�ĵȼ�Ϊ1������
		{
			if(richerplayer->getTag() == PLAYER_2_TAG)   //����ǽ�ɫ2
			{
				//����������ͼ��Ϣ
				__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_BUY_LAND_1_TAG,x,y,richerplayer->getTag());
				NotificationCenter::getInstance()->postNotification(MSG_BUY,msgStr); 
			}
			else
			{
				//����·��
				__String * str = __String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_1_TAG,x,y,richerplayer->getTag());
                NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);  
			}
			return;
		}
		if(titleId == GameBaseLayer::player2_building_2_tiledID)   //�Ƿ��ǽ�ɫ2�ĵȼ�Ϊ2������
		{
			if(richerplayer->getTag() == PLAYER_2_TAG)   //����ǽ�ɫ2
			{
				//����������ͼ��Ϣ
				__String *msgStr = __String::createWithFormat("%d-%f-%f-%d",MSG_BUY_LAND_2_TAG,x,y,richerplayer->getTag());
				NotificationCenter::getInstance()->postNotification(MSG_BUY,msgStr); 
			}
			else
			{
				//����·��
				__String * str = __String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_2_TAG,x,y,richerplayer->getTag());
                NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);  
			}
			return;
		}
		if(titleId == GameBaseLayer::player2_building_3_tiledID)   //�Ƿ��ǽ�ɫ2�ĵȼ�Ϊ3������
		{
			if(richerplayer->getTag() == PLAYER_2_TAG)   //����ǽ�ɫ2
			{
				//ʲô��������������Ϣ������һ����ɫ����
				NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,__String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG)); 
			}
			else
			{
				//����·��
				__String * str = __String::createWithFormat("%d-%f-%f-%d",MSG_PAY_TOLLS_3_TAG,x,y,richerplayer->getTag());
                NotificationCenter::getInstance()->postNotification(MSG_PAY_TOLLS,str);  
			}
			return;
		}
	}
	//�����ɫ��ǰλ���������Ҷ�û�����أ�������Ϣ��������һ����ɫ����
	NotificationCenter::getInstance()->postNotification(MSG_PICKONE_TOGO,__String::createWithFormat("%d",MSG_PICKONE_TOGO_TAG));
}

void RicherGameController::addNotificationObserver()
{
	//ע�����MSG_PICKONE_TOGO�ļ���������������һ����ɫ�����¼�
	NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(RicherGameController::receiveMsg),
		MSG_PICKONE_TOGO,
		NULL);

	//ע�����MSG_RANDOM_ASK_EVENT�ļ�����,�����ʺ�����¼�
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