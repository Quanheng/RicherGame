#ifndef __GAME_BASE_SCENE_H__
#define __GAME_BASE_SCENE_H__

#include "cocos2d.h"
#include "ConstUtil.h"
#include "RicherPlayer.h"
#include "RouteNavigation.h"
#include "RicherGameController.h"
#include "PopupLayer.h"
#include "CocosToast.h"
#include "SkillCard.h"

USING_NS_CC;

const int tableStartPosition_x = 650;
const int tableStartPosition_y = 400;
const int tableWidth = 50;
const int tableHeight = 40;

const int GO_MENU_ITEM_TAG =351;
const int SKILL_MENU_ITEM_TAG =352;
const int MENU_TAG = 353;
const int skillStormTag = 354;
const int skillTransferTag = 355;
const int saveButtonTag = 356;

const int skillSpriteCardWidth = 150;
const int skillSpriteCardHeight = 100;

const int Dialog_Size_Width = 400;
const int Dialog_Size_Height = 220;

const int Btn_OK_TAG = 1;
const int Btn_Cancel_TAG = 0;

class GameBaseLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();	
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();       //退出时，释放某些变量空间

	static int blank_land_tiledID;
	static int strength_30_tiledID;
	static int strength_50_tiledID;
	static int strength_80_tiledID;

	static int randomEvent_tiledID;
	static int lottery_tiledID;
	static int stock_tiledID;

	static int player1_building_1_tiledID;
	static int player1_building_2_tiledID;
	static int player1_building_3_tiledID;

	static int player2_building_1_tiledID;
	static int player2_building_2_tiledID;
	static int player2_building_3_tiledID;

	RicherPlayer *player1;       //角色1
	RicherPlayer *player2;
	RicherPlayer *player3;
	
	static Vector<RicherPlayer*> players_vector;        //存放角色的容器

	//virtual void addMap();       //添加地图     
	static cocos2d::TMXTiledMap* _map;      //定义地图
	static cocos2d::TMXLayer *wayLayer;    //地图way层
	static cocos2d::TMXLayer *landLayer;   //地图land层

	static int tiledColsCount;          //关卡地图总列数
	static int tiledRowsCount;          //关卡地图总行数	

	static bool **canPassGrid;          //根据地图总的行列数创建一个二维数组		

	//virtual void initTiledGrid();              //初始化canPassGrid数组
	//virtual void initPropTiledID();  //初始化道具ID

	void setWayPassToGrid();                   //根据图层way，设置canPassGrid数组相应的值为true
	std::vector<cocos2d::Vec2> wayLayerPass_Vector;//保存路径坐标的容器

	void initLandLayerFromMap();     //初始化landLayer	
	

	float buy_land_x;                //要购买的土地的x坐标
	float buy_land_y;                //要购买的土地的y坐标	
	
	static Vector<Sprite*> pathMarkVector;              //存放6个遮挡路径的精灵

	void addPathMark();                 //添加遮挡精灵
	static void drawPathMark(std::vector<int> rowVector,std::vector<int> colVector);        //绘制路径 

	void addNotificationObserver();     //添加消息接收器
	void receiveNotificationOMsg(cocos2d::Ref *pSender);  //接收消息后处理函数

	void sendMSGPickOneToGO(float dt);  //发送消息，让下一个角色走
	void sendMSGDealLandRound(float dt);  //发送消息，处理角色周围的土地情况，购买或缴费

	void addPlayerInfo();         //添加角色信息
	void addDigiteRoundSprite();  //回合数字精灵帧
	void refresshRoundDisplay();  //更新回合数

	PopupLayer *popDialog;       //创建对话框对象
	void initPopDialog();        //初始化购买土地对话框
	void buyLandCallBack(cocos2d::Node* node); //购买土地回调函数
	void showBuyLandDialog(int landTag);    //显示对话框	

	CREATE_FUNC(GameBaseLayer);


private:
	void drawTable(int playerNumber);                 //根据上边定义的变量画表格，用来放置角色
	void addPlayer();                                 //添加游戏角色部分信息方法，在控制栏显示头像，资金，体力等
	void addRightBanner();                            //添加右边地图空白部分背景，上方放置人物等信息

	cocos2d::MenuItem *goMenuItem;                    //go摇骰子按钮
	cocos2d::MenuItem *skillMenuItem;                 //技能按钮
	int transferLandTag;                              //夺取的土地的tag
	SkillCard *skillStorm;                            //暴风骤雨技能界面
	SkillCard *skillTransfer;                         //巧取豪夺技能界面
	void addGoButton();                               //添加按钮

	//按钮回调函数
	void goButtomCallback(cocos2d::Ref* pSender);              
	void skillStormCallback(cocos2d::Node* node);
	void skillTransferCallback(cocos2d::Node* node);

	bool isShowSkillLayer;        //是否显示技能界面

	void showSkillSprites();      //显示/隐藏技能界面函数

	CC_SYNTHESIZE(Label*,player1_money_label,Player1_money_label);       //显示角色1当前的金钱的Label
	CC_SYNTHESIZE(Label*,player2_money_label,Player2_money_label);       //显示角色2当前的金钱的Label
	CC_SYNTHESIZE(Label*,player1_strength_label,Player1_strength_label);	//显示角色1当前的体力的Label
	CC_SYNTHESIZE(Label*,player2_strength_label,Player2_strength_label); //显示角色2当前的体力的Label

	CC_SYNTHESIZE(Menu*,menu,Menu);                 //包括go、技能等菜单项的菜单

	int gameRoundCount;       //回合计数
	Vector<SpriteFrame*> digitalRoundVector;   //存放0~9数字的精灵帧缓存
	Vector<Sprite*> refreshRoundVector; 	
	
	void addDice();      //添加骰子
	CC_SYNTHESIZE(Animate*,diceAnimate,DiceAnimate);         //骰子动画
	CC_SYNTHESIZE(Sprite*,diceSprite,DiceSprite);            //骰子精灵
	cocos2d::SpriteFrameCache *diceFrameCache;               //骰子精灵帧缓存
	int randNumber ;                                         //点数

	void particleForBuyLand();       //购买土地时的效果（加载脚印精灵的动作）
	cocos2d::ActionInterval *scaleBy1ForBuyLand;     //购买土地动作1,放大
	cocos2d::ActionInterval *scaleBy2ForBuyLand;     //购买土地动作2，缩小
	cocos2d::ActionInterval *landFadeOut;            //淡出
	cocos2d::ActionInterval *landFadeIn;             //淡入
	cocos2d::Sprite *foot1Sprite;    //代表角色1的土地的精灵
	cocos2d::Sprite *foot2Sprite;    //代表角色2的土地的精灵
	cocos2d::Sprite *star1Sprite;    //海星1精灵
	cocos2d::Sprite *star2Sprite;    //海星2精灵
	cocos2d::Sprite *heart1Sprite;  //心形1精灵
	cocos2d::Sprite *heart2Sprite;  //心形2精灵
	void playParticle(cocos2d::Vec2 point,char *plistName);             //播放效果

	void buyLand(int buyTag,float x,float y,cocos2d::Sprite *landSprite,int landLevel, RicherPlayer *player,char *particlelistName);    //购买土地函数

	RicherPlayer* getPlayerByTiled(float x,float y);    //根据位置坐标，获取土地的所属角色
	void payTolls(int payTollTag,float x,float y,int playerTag);     //缴纳过路费
	void refreshMoney(RicherPlayer *player,int money);       //更新金钱	

	cocos2d::Map<int,__String*> randomAskEventMap;   //存放随机事件的描述字符串的Map容器
	void initRandomAskEventMap();                    //初始化Map容器
	void doRandomAskEvent(RicherPlayer* player);     //处理问号随机事件

	void doStrengthUpEvent(int strngthUp,int playerTag);            //捡到积分卡，增加体力
	void refreshStrength(RicherPlayer *player,int strength);        //更新体力
	cocos2d::SpriteFrameCache *strengthUpFrameCache;                     //体力回升的精灵帧缓存	
	CC_SYNTHESIZE(Animate*,strengthUpAnimate,StrengthUpAnimate);         //体力回升的动画
	CC_SYNTHESIZE(Sprite*,strengthUpSprite,StrengthUpSprite);            //体力回升的精灵
	void addPlayerStrengthUpAniate();                                    //添加体力回升动画的函数
	
	void initAudioEffect();
	Vector<__String*> player2EffectVec_1;  //交过路费声音0-6
	Vector<__String*> player2EffectVec_2;  //抢夺别人地块7-10
	Vector<__String*> player2EffectVec_3;  //房屋被抢夺11-14
	Vector<__String*> player2EffectVec_4;  //摧毁别人房屋15-18
	Vector<__String*> player2EffectVec_5;  //房屋被摧毁19-22

	Vector<__String*> player2EffectVec_6;  // 收取过路费23 - 28
	Vector<__String*> player2EffectVec_7;  //升级房子29-30
	Vector<__String*> player2EffectVec_8;  // 买地31 - 34
	Vector<__String*> player2EffectVec_9;  //对方被罚收税35-38

	Vector<__String*> player1EffectVec_1;  //交过路费声音
	Vector<__String*> player1EffectVec_2;  //抢夺别人地块
	Vector<__String*> player1EffectVec_3;  //房屋被抢夺
	Vector<__String*> player1EffectVec_4;  //摧毁别人房屋
	Vector<__String*> player1EffectVec_5;  //房屋被摧毁

	Vector<__String*> player1EffectVec_6;  // 收取过路费
	Vector<__String*> player1EffectVec_7;  //升级房子
	Vector<__String*> player1EffectVec_8;  // 买地
	Vector<__String*> player1EffectVec_9;  //对方被罚收税

	Vector<__String*> nextPlayerEffectVec;
	void playNextEffectVec(float t);

	
};

#endif