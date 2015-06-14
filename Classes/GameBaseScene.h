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
	virtual void onExit();       //�˳�ʱ���ͷ�ĳЩ�����ռ�

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

	RicherPlayer *player1;       //��ɫ1
	RicherPlayer *player2;
	RicherPlayer *player3;
	
	static Vector<RicherPlayer*> players_vector;        //��Ž�ɫ������

	//virtual void addMap();       //��ӵ�ͼ     
	static cocos2d::TMXTiledMap* _map;      //�����ͼ
	static cocos2d::TMXLayer *wayLayer;    //��ͼway��
	static cocos2d::TMXLayer *landLayer;   //��ͼland��

	static int tiledColsCount;          //�ؿ���ͼ������
	static int tiledRowsCount;          //�ؿ���ͼ������	

	static bool **canPassGrid;          //���ݵ�ͼ�ܵ�����������һ����ά����		

	//virtual void initTiledGrid();              //��ʼ��canPassGrid����
	//virtual void initPropTiledID();  //��ʼ������ID

	void setWayPassToGrid();                   //����ͼ��way������canPassGrid������Ӧ��ֵΪtrue
	std::vector<cocos2d::Vec2> wayLayerPass_Vector;//����·�����������

	void initLandLayerFromMap();     //��ʼ��landLayer	
	

	float buy_land_x;                //Ҫ��������ص�x����
	float buy_land_y;                //Ҫ��������ص�y����	
	
	static Vector<Sprite*> pathMarkVector;              //���6���ڵ�·���ľ���

	void addPathMark();                 //����ڵ�����
	static void drawPathMark(std::vector<int> rowVector,std::vector<int> colVector);        //����·�� 

	void addNotificationObserver();     //�����Ϣ������
	void receiveNotificationOMsg(cocos2d::Ref *pSender);  //������Ϣ������

	void sendMSGPickOneToGO(float dt);  //������Ϣ������һ����ɫ��
	void sendMSGDealLandRound(float dt);  //������Ϣ�������ɫ��Χ����������������ɷ�

	void addPlayerInfo();         //��ӽ�ɫ��Ϣ
	void addDigiteRoundSprite();  //�غ����־���֡
	void refresshRoundDisplay();  //���»غ���

	PopupLayer *popDialog;       //�����Ի������
	void initPopDialog();        //��ʼ���������ضԻ���
	void buyLandCallBack(cocos2d::Node* node); //�������ػص�����
	void showBuyLandDialog(int landTag);    //��ʾ�Ի���	

	CREATE_FUNC(GameBaseLayer);


private:
	void drawTable(int playerNumber);                 //�����ϱ߶���ı���������������ý�ɫ
	void addPlayer();                                 //�����Ϸ��ɫ������Ϣ�������ڿ�������ʾͷ���ʽ�������
	void addRightBanner();                            //����ұߵ�ͼ�հײ��ֱ������Ϸ������������Ϣ

	cocos2d::MenuItem *goMenuItem;                    //goҡ���Ӱ�ť
	cocos2d::MenuItem *skillMenuItem;                 //���ܰ�ť
	int transferLandTag;                              //��ȡ�����ص�tag
	SkillCard *skillStorm;                            //�������꼼�ܽ���
	SkillCard *skillTransfer;                         //��ȡ���Ἴ�ܽ���
	void addGoButton();                               //��Ӱ�ť

	//��ť�ص�����
	void goButtomCallback(cocos2d::Ref* pSender);              
	void skillStormCallback(cocos2d::Node* node);
	void skillTransferCallback(cocos2d::Node* node);

	bool isShowSkillLayer;        //�Ƿ���ʾ���ܽ���

	void showSkillSprites();      //��ʾ/���ؼ��ܽ��溯��

	CC_SYNTHESIZE(Label*,player1_money_label,Player1_money_label);       //��ʾ��ɫ1��ǰ�Ľ�Ǯ��Label
	CC_SYNTHESIZE(Label*,player2_money_label,Player2_money_label);       //��ʾ��ɫ2��ǰ�Ľ�Ǯ��Label
	CC_SYNTHESIZE(Label*,player1_strength_label,Player1_strength_label);	//��ʾ��ɫ1��ǰ��������Label
	CC_SYNTHESIZE(Label*,player2_strength_label,Player2_strength_label); //��ʾ��ɫ2��ǰ��������Label

	CC_SYNTHESIZE(Menu*,menu,Menu);                 //����go�����ܵȲ˵���Ĳ˵�

	int gameRoundCount;       //�غϼ���
	Vector<SpriteFrame*> digitalRoundVector;   //���0~9���ֵľ���֡����
	Vector<Sprite*> refreshRoundVector; 	
	
	void addDice();      //�������
	CC_SYNTHESIZE(Animate*,diceAnimate,DiceAnimate);         //���Ӷ���
	CC_SYNTHESIZE(Sprite*,diceSprite,DiceSprite);            //���Ӿ���
	cocos2d::SpriteFrameCache *diceFrameCache;               //���Ӿ���֡����
	int randNumber ;                                         //����

	void particleForBuyLand();       //��������ʱ��Ч�������ؽ�ӡ����Ķ�����
	cocos2d::ActionInterval *scaleBy1ForBuyLand;     //�������ض���1,�Ŵ�
	cocos2d::ActionInterval *scaleBy2ForBuyLand;     //�������ض���2����С
	cocos2d::ActionInterval *landFadeOut;            //����
	cocos2d::ActionInterval *landFadeIn;             //����
	cocos2d::Sprite *foot1Sprite;    //�����ɫ1�����صľ���
	cocos2d::Sprite *foot2Sprite;    //�����ɫ2�����صľ���
	cocos2d::Sprite *star1Sprite;    //����1����
	cocos2d::Sprite *star2Sprite;    //����2����
	cocos2d::Sprite *heart1Sprite;  //����1����
	cocos2d::Sprite *heart2Sprite;  //����2����
	void playParticle(cocos2d::Vec2 point,char *plistName);             //����Ч��

	void buyLand(int buyTag,float x,float y,cocos2d::Sprite *landSprite,int landLevel, RicherPlayer *player,char *particlelistName);    //�������غ���

	RicherPlayer* getPlayerByTiled(float x,float y);    //����λ�����꣬��ȡ���ص�������ɫ
	void payTolls(int payTollTag,float x,float y,int playerTag);     //���ɹ�·��
	void refreshMoney(RicherPlayer *player,int money);       //���½�Ǯ	

	cocos2d::Map<int,__String*> randomAskEventMap;   //�������¼��������ַ�����Map����
	void initRandomAskEventMap();                    //��ʼ��Map����
	void doRandomAskEvent(RicherPlayer* player);     //�����ʺ�����¼�

	void doStrengthUpEvent(int strngthUp,int playerTag);            //�񵽻��ֿ�����������
	void refreshStrength(RicherPlayer *player,int strength);        //��������
	cocos2d::SpriteFrameCache *strengthUpFrameCache;                     //���������ľ���֡����	
	CC_SYNTHESIZE(Animate*,strengthUpAnimate,StrengthUpAnimate);         //���������Ķ���
	CC_SYNTHESIZE(Sprite*,strengthUpSprite,StrengthUpSprite);            //���������ľ���
	void addPlayerStrengthUpAniate();                                    //����������������ĺ���
	
	void initAudioEffect();
	Vector<__String*> player2EffectVec_1;  //����·������0-6
	Vector<__String*> player2EffectVec_2;  //������˵ؿ�7-10
	Vector<__String*> player2EffectVec_3;  //���ݱ�����11-14
	Vector<__String*> player2EffectVec_4;  //�ݻٱ��˷���15-18
	Vector<__String*> player2EffectVec_5;  //���ݱ��ݻ�19-22

	Vector<__String*> player2EffectVec_6;  // ��ȡ��·��23 - 28
	Vector<__String*> player2EffectVec_7;  //��������29-30
	Vector<__String*> player2EffectVec_8;  // ���31 - 34
	Vector<__String*> player2EffectVec_9;  //�Է�������˰35-38

	Vector<__String*> player1EffectVec_1;  //����·������
	Vector<__String*> player1EffectVec_2;  //������˵ؿ�
	Vector<__String*> player1EffectVec_3;  //���ݱ�����
	Vector<__String*> player1EffectVec_4;  //�ݻٱ��˷���
	Vector<__String*> player1EffectVec_5;  //���ݱ��ݻ�

	Vector<__String*> player1EffectVec_6;  // ��ȡ��·��
	Vector<__String*> player1EffectVec_7;  //��������
	Vector<__String*> player1EffectVec_8;  // ���
	Vector<__String*> player1EffectVec_9;  //�Է�������˰

	Vector<__String*> nextPlayerEffectVec;
	void playNextEffectVec(float t);

	
};

#endif