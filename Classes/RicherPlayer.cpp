#include "RicherPlayer.h"
#include "RicherGameController.h"
#include "GameBaseScene.h"

USING_NS_CC;


RicherPlayer::RicherPlayer()
{
}
RicherPlayer::~RicherPlayer()
{
	left->release();
	right->release();
	down->release();
	up->release();
	rain_skill_animate->release();
	transfer_skill_animate->release();
}


RicherPlayer* RicherPlayer::create(char *name,int tag,bool isEnemy,int money,int strength){
	RicherPlayer *player = new RicherPlayer();
	player->init(name,tag,isEnemy, money,strength);
	return player;
}

bool RicherPlayer::init(char *name,int tag,bool isEnemy,int money,int strength)
{
	this->setTag(tag);
	addPlayerAnimation();
	setPlayerAnimate();
	addSkillAnimate();
	SpriteFrame *spf;
	switch(tag)
	{
	case PLAYER_1_TAG:
		spf = player_SpriteFrameCache->getSpriteFrameByName("player1_anim_01.png");
		break;
	case PLAYER_2_TAG:
		spf = player_SpriteFrameCache->getSpriteFrameByName("player2_anim_01.png");
		break;
	}
	Sprite::initWithSpriteFrame(spf);
	_name = name;
	_isEnemy =isEnemy;
	_money = money;
	_strength = strength;
	isMyTurn =true;
	comeFromRow =-1;
	comeFromCol =-1;

	//初始化停留位置
	stop_x = -100;
	stop_y = 0;

	return true;
}

void RicherPlayer::addPlayerAnimation()
{   
	//创建player的帧缓存，并加载到缓存
	player_SpriteFrameCache = SpriteFrameCache::getInstance();
	int tag = this->getTag();	
	switch(tag)
	{
	case PLAYER_1_TAG:		
	    player_SpriteFrameCache->addSpriteFramesWithFile("map/player1_anim.plist");
		break;
	case PLAYER_2_TAG:
		player_SpriteFrameCache->addSpriteFramesWithFile("map/player2_anim.plist");
		break;
	}
		

	//第1-4张图片是表示向左的动画，将这四张图片取出来，分辨保存到相应角色的vector中
	for(int i=1;i<=4;i++)
	{
		__String *frameName = __String::createWithFormat("player%d_anim_%02d.png",tag,i);
		player_anim_left_vector.pushBack(player_SpriteFrameCache->getSpriteFrameByName(frameName->getCString()));
	}
	//向右的动画
	for(int i=5;i<=8;i++)
	{
		__String *frameName = __String::createWithFormat("player%d_anim_%02d.png",tag,i);
		player_anim_right_vector.pushBack(player_SpriteFrameCache->getSpriteFrameByName(frameName->getCString()));
	}
	//向下的动画
	for(int i=9;i<=12;i++)
	{
		__String *frameName = __String::createWithFormat("player%d_anim_%02d.png",tag,i);
		player_anim_down_vector.pushBack(player_SpriteFrameCache->getSpriteFrameByName(frameName->getCString()));
	}
	//向上的动画
	for(int i=13;i<=16;i++)
	{
		__String *frameName = __String::createWithFormat("player%d_anim_%02d.png",tag,i);
		player_anim_up_vector.pushBack(player_SpriteFrameCache->getSpriteFrameByName(frameName->getCString()));
	}
	
}

void RicherPlayer::setPlayerAnimate()
{ 
	//定义角色上下左右四个方向的动画
	Animation *player_animation_left = Animation::createWithSpriteFrames(player_anim_left_vector,playerGoPerFrameTime);
	Animation *player_animation_right = Animation::createWithSpriteFrames(player_anim_right_vector,playerGoPerFrameTime);
	Animation *player_animation_down = Animation::createWithSpriteFrames(player_anim_down_vector,playerGoPerFrameTime);
	Animation *player_animation_up = Animation::createWithSpriteFrames(player_anim_up_vector,playerGoPerFrameTime);

	player_anim_left_vector.size();
	player_anim_up_vector.size();
	//定义角色上下左右四个方向的动作
	left = Animate::create(player_animation_left);
	right =Animate::create(player_animation_right);
	down =Animate::create(player_animation_down);
	up = Animate::create(player_animation_up);
	 
	left->retain();
	right->retain();
	down->retain();
	up->retain();
}

void RicherPlayer::addSkillAnimate()
{
	//创建技能的帧缓存，并加载到缓存
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("images/rain.plist");
	spriteFrameCache->addSpriteFramesWithFile("images/change.plist");

	for(int i=1;i<=19;i++)
	{
		__String *frameName = __String::createWithFormat("rain_%02d.png",i);
		skill_rain_vector.pushBack(spriteFrameCache->getSpriteFrameByName(frameName->getCString()));
	}

	for(int i=1;i<=32;i++)
	{
		__String *frameName = __String::createWithFormat("change_%02d.png",i);
		skill_transfer_vector.pushBack(spriteFrameCache->getSpriteFrameByName(frameName->getCString()));
	}

	//定义暴风骤雨技能的动画
	Animation *rain_nimation = Animation::createWithSpriteFrames(skill_rain_vector,0.1f);

	//定义巧取豪夺技能的动画
	Animation *transfer_animation = Animation::createWithSpriteFrames(skill_transfer_vector,0.1f);

	rain_skill_animate = Animate::create(rain_nimation);
	transfer_skill_animate = Animate::create(transfer_animation);
	
	rain_skill_animate->retain();
	transfer_skill_animate->retain();

}


void RicherPlayer::startGo(std::vector<int> rowVector,std::vector<int> colVector)
{
	auto callFunc = CallFunc::create([rowVector,colVector,this](){
		RicherGameController::getInstance()->startRealGo(rowVector,colVector,this);
	});
	FiniteTimeAction *fadeOut = FadeOut::create(0.2);
	FiniteTimeAction *fadeIn = FadeIn::create(0.2);

	GameBaseLayer::drawPathMark(rowVector,colVector);

	this->runAction(Sequence::create(fadeOut,fadeIn,callFunc,NULL));
}