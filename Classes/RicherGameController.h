#ifndef __RICHER_GAME_CONTROLLER_H__
#define __RICHER_GAME_CONTROLLER_H__

#include "cocos2d.h"
#include "RicherPlayer.h"
#include "Util.h"

USING_NS_CC;



class RicherGameController  : public cocos2d::Layer   //���̳�Layer����Ӳ�����Ϣ������������
{
public:
	static RicherGameController *rgContreoller_Instance;
	static RicherGameController *getInstance();

	virtual bool init();   

	void startRealGo(std::vector<int> rowVector,std::vector<int> colVector,RicherPlayer *player);
	void moveOneStep(RicherPlayer *player);    //ִ�н�ɫ��һ�����ƶ��Ͷ���
	void endMove();          //ÿ����һ�������øú����ú������ж��Ƿ��ѽ����������в�����������������ŵ���moveOneStep��������	
	void pickOnePlayerToGo();   //������ɫ����
	void handlePropEvent();    //��������¼����ʺ��¼��ȣ�
	void handleLandEvent();    //�������ص��¼����������ء��������ء�����·�ѣ�

	void addNotificationObserver();   //�����Ϣ������
	void receiveMsg(cocos2d::Ref *pSender);  //�յ���Ϣʱ�����д���            
	
private:
	RicherGameController();
	~RicherGameController();

	CC_SYNTHESIZE(int,stepHasGone,StepHasGone);        //��¼���߲���
	CC_SYNTHESIZE(int,stepCount,StepCount);            //�ܲ��� 
	CC_SYNTHESIZE(int,currentRow,CurrentRow);          //��ǰλ�õ�����
	CC_SYNTHESIZE(int,currentCol,CurrentCol);          //��ǰλ�õ�����
	CC_SYNTHESIZE(int,nextRow,NextRow);                //һ�²�λ�õĵ�����
	CC_SYNTHESIZE(int,nextCol,NextCol);                //һ�²�λ�õĵ�����
	CC_SYNTHESIZE(bool,oneRoundDone,OneRoundDone);     //�غ��Ƿ���� 
	std::vector<int> _rowVector;
	std::vector<int> _colVector;
	cocos2d::FiniteTimeAction *moveBy;
	cocos2d::FiniteTimeAction *repeat;
	cocos2d::ActionInterval *spawnAction;
	cocos2d::FiniteTimeAction *callEndFunc;                //����endMove��������
	RicherPlayer *richerplayer;
};

#endif