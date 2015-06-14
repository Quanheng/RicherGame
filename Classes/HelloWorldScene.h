#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ConstUtil.h"
#include "MenuScene.h"

class HelloWorld : public cocos2d::Layer
{
private:
	cocos2d::Sprite *a_Sprite;
	cocos2d::Sprite *b_Sprite;
	cocos2d::Sprite *c_Sprite;
	cocos2d::Sprite *d_Sprite;

	cocos2d::Size spriteSize;    //每张图片的尺寸

	         //动画的播放速度

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void moveSprite(float dt);       //第一次移动图片
	void moveSprite_2();             //第二次移动图片

	void spriteFadeOut();            //动画完后，渐渐消失

	void gotoMenuScene();     //进入菜单场景
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
