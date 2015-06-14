#ifndef __RICHER_PLAYER_H__
#define __RICHER_PLAYER_H__

#include "cocos2d.h"
#include "ConstUtil.h"

USING_NS_CC;

const float playerGoTotalTime = 0.28f;
const float playerGoPerFrameTime = 0.07f;

class RicherPlayer : public cocos2d::Sprite
{
public:
	RicherPlayer();
	~RicherPlayer();
	cocos2d::SpriteFrameCache *player_SpriteFrameCache;
	static RicherPlayer* create(char *name,int tag ,bool isEnemy,int money=200000,int strength=100);
	
	bool init(char *name,int tag,bool isEnemy,int money,int strength);
	void startGo(std::vector<int> rowVector , std::vector<int> colVector);

	void addPlayerAnimation();         //���ض����ļ����ڴ棬��������ɫ���������ĸ�����Ķ���
	void setPlayerAnimate();           //������ɫ���������ĸ�����Ķ���

	//����player�ĸ�����ľ���֡����
	CC_SYNTHESIZE(Vector<SpriteFrame*>,player_anim_left_vector,Player_anim_left_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame*>,player_anim_right_vector,Player_anim_right_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame*>,player_anim_down_vector,Player_anim_down_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame*>,player_anim_up_vector,Player_anim_up_vector);

	CC_SYNTHESIZE(Animate*,left,Left);        //����player����Ķ���
	CC_SYNTHESIZE(Animate*,right,Right);      //����player���ҵĶ���
	CC_SYNTHESIZE(Animate*,down,Down);        //����player���µĶ���
	CC_SYNTHESIZE(Animate*,up,Up);            //����player���ϵĶ���


	void addSkillAnimate();        //��Ӽ��ܶ���

	CC_SYNTHESIZE(Vector<SpriteFrame*>,skill_rain_vector,Skill_rain_vector);               //�������꼼�ܵ�SpriteFrame����
	CC_SYNTHESIZE(Vector<SpriteFrame*>,skill_transfer_vector,Skill_transfer_vector);       //��ȡ���Ἴ��...

	CC_SYNTHESIZE(Animate*,rain_skill_animate,Rain_skill_animate);                  //�������꼼�ܶ���
	CC_SYNTHESIZE(Animate*,transfer_skill_animate,Transfer_skill_animate);          //��ȡ���Ἴ�ܶ���

private:
	CC_SYNTHESIZE(std::string,_name,Name);      //��ɫ��
	CC_SYNTHESIZE(bool,_isEnemy,Enemy);        //��ɫ����
	CC_SYNTHESIZE(int,_money,Money);       //��Ǯ
	CC_SYNTHESIZE(int,_strength,Strength);    //����
	CC_SYNTHESIZE(int,comeFromRow,ComeFromRow);    //��¼������λ�õ��б꣨��һ�����������߻�ͷ
	CC_SYNTHESIZE(int,comeFromCol,ComFromCol);     //��¼������λ�õ��б꣨��һ����
	CC_SYNTHESIZE(bool,isMyTurn,IsMyTurn);        //�Ƿ�����    

	CC_SYNTHESIZE(int,stop_x,Stop_x);       //ͣ��λ�õ�x����
	CC_SYNTHESIZE(int,stop_y,Stop_y);       //ͣ��λ�õ�y����
};


#endif



