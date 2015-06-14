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

	void addPlayerAnimation();         //加载动画文件到内存，并创建角色上下左右四个方向的动画
	void setPlayerAnimate();           //创建角色上下左右四个方向的动作

	//创建player四个方向的精灵帧容器
	CC_SYNTHESIZE(Vector<SpriteFrame*>,player_anim_left_vector,Player_anim_left_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame*>,player_anim_right_vector,Player_anim_right_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame*>,player_anim_down_vector,Player_anim_down_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame*>,player_anim_up_vector,Player_anim_up_vector);

	CC_SYNTHESIZE(Animate*,left,Left);        //定义player向左的动作
	CC_SYNTHESIZE(Animate*,right,Right);      //定义player向右的动作
	CC_SYNTHESIZE(Animate*,down,Down);        //定义player向下的动作
	CC_SYNTHESIZE(Animate*,up,Up);            //定义player向上的动作


	void addSkillAnimate();        //添加技能动画

	CC_SYNTHESIZE(Vector<SpriteFrame*>,skill_rain_vector,Skill_rain_vector);               //暴风骤雨技能的SpriteFrame容器
	CC_SYNTHESIZE(Vector<SpriteFrame*>,skill_transfer_vector,Skill_transfer_vector);       //巧取豪夺技能...

	CC_SYNTHESIZE(Animate*,rain_skill_animate,Rain_skill_animate);                  //暴风骤雨技能动画
	CC_SYNTHESIZE(Animate*,transfer_skill_animate,Transfer_skill_animate);          //巧取豪夺技能动画

private:
	CC_SYNTHESIZE(std::string,_name,Name);      //角色名
	CC_SYNTHESIZE(bool,_isEnemy,Enemy);        //角色类型
	CC_SYNTHESIZE(int,_money,Money);       //金钱
	CC_SYNTHESIZE(int,_strength,Strength);    //体力
	CC_SYNTHESIZE(int,comeFromRow,ComeFromRow);    //记录过来的位置的行标（上一步），避免走回头
	CC_SYNTHESIZE(int,comeFromCol,ComFromCol);     //记录过来的位置的列标（上一步）
	CC_SYNTHESIZE(bool,isMyTurn,IsMyTurn);        //是否能走    

	CC_SYNTHESIZE(int,stop_x,Stop_x);       //停留位置的x坐标
	CC_SYNTHESIZE(int,stop_y,Stop_y);       //停留位置的y坐标
};


#endif



