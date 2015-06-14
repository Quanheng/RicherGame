#ifndef __RICHER_GAME_CONTROLLER_H__
#define __RICHER_GAME_CONTROLLER_H__

#include "cocos2d.h"
#include "RicherPlayer.h"
#include "Util.h"

USING_NS_CC;



class RicherGameController  : public cocos2d::Layer   //不继承Layer，添加不了消息监听器？？？
{
public:
	static RicherGameController *rgContreoller_Instance;
	static RicherGameController *getInstance();

	virtual bool init();   

	void startRealGo(std::vector<int> rowVector,std::vector<int> colVector,RicherPlayer *player);
	void moveOneStep(RicherPlayer *player);    //执行角色下一步的移动和动画
	void endMove();          //每走完一步，调用该函数该函数，判断是否已结走完了所有步数，是则结束，否着调用moveOneStep，继续走	
	void pickOnePlayerToGo();   //其他角色行走
	void handlePropEvent();    //处理道具事件（问号事件等）
	void handleLandEvent();    //处理土地的事件（购买土地、升级土地、缴纳路费）

	void addNotificationObserver();   //添加消息监听器
	void receiveMsg(cocos2d::Ref *pSender);  //收到消息时，进行处理            
	
private:
	RicherGameController();
	~RicherGameController();

	CC_SYNTHESIZE(int,stepHasGone,StepHasGone);        //记录已走步数
	CC_SYNTHESIZE(int,stepCount,StepCount);            //总步数 
	CC_SYNTHESIZE(int,currentRow,CurrentRow);          //当前位置的行数
	CC_SYNTHESIZE(int,currentCol,CurrentCol);          //当前位置的列数
	CC_SYNTHESIZE(int,nextRow,NextRow);                //一下步位置的的行数
	CC_SYNTHESIZE(int,nextCol,NextCol);                //一下步位置的的列数
	CC_SYNTHESIZE(bool,oneRoundDone,OneRoundDone);     //回合是否结束 
	std::vector<int> _rowVector;
	std::vector<int> _colVector;
	cocos2d::FiniteTimeAction *moveBy;
	cocos2d::FiniteTimeAction *repeat;
	cocos2d::ActionInterval *spawnAction;
	cocos2d::FiniteTimeAction *callEndFunc;                //调用endMove（）函数
	RicherPlayer *richerplayer;
};

#endif