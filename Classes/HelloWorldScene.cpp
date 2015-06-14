#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	

    //³õÊ¼»¯Í¼Æ¬
	a_Sprite = Sprite::create(A_IMAGE);
	b_Sprite = Sprite::create(B_IMAGE);
	c_Sprite = Sprite::create(C_IMAGE);

	spriteSize = a_Sprite->getContentSize();

	c_Sprite->setPosition(Vec2(origin.x + visibleSize.width/2 , origin.y +  visibleSize.height/2));
	b_Sprite->setPosition(Vec2(origin.x + visibleSize.width/2  - spriteSize.width , origin.y +  visibleSize.height/2));
	a_Sprite->setPosition(Vec2(origin.x + visibleSize.width/2  + spriteSize.width , origin.y +  visibleSize.height/2));
    
	a_Sprite->setAnchorPoint(Vec2(0.5f,0.5f));
	b_Sprite->setAnchorPoint(Vec2(0.5f,0.5f));
	c_Sprite->setAnchorPoint(Vec2(0.5f,0.5f));

	this->addChild(a_Sprite,1);
	this->addChild(b_Sprite,1);
	this->addChild(c_Sprite,1);
	scheduleOnce(schedule_selector(HelloWorld::moveSprite),1.0f);

    return true;
}


void HelloWorld::moveSprite(float dt)
{
	a_Sprite->runAction(MoveBy::create(1,Vec2(-spriteSize.width ,0)));   //¾«Áé×óÒÆ

    auto c_move=MoveBy::create(1,Vec2(spriteSize.width ,0));    //ÓÒÒÆ¶¯×÷

	CallFunc *callFunc = CallFunc::create(CC_CALLBACK_0(HelloWorld::moveSprite_2,this));    

	c_Sprite->runAction(Sequence::create(c_move,callFunc,NULL)); 
}

void HelloWorld::moveSprite_2()
{
	a_Sprite->runAction(MoveBy::create(1,Vec2(-spriteSize.width ,0)));   //¾«Áé×óÒÆ

    auto b_move=MoveBy::create(1,Vec2(spriteSize.width ,0));    //ÓÒÒÆ¶¯×÷

	CallFunc *callFunc = CallFunc::create(CC_CALLBACK_0(HelloWorld::spriteFadeOut,this));    

	b_Sprite->runAction(Sequence::create(b_move,callFunc,NULL)); 
}

void HelloWorld::spriteFadeOut()
{
	a_Sprite->runAction(FadeOut::create(2.0f));
	b_Sprite->runAction(FadeOut::create(2.0f));

	auto  c_FadeOut = FadeOut::create(2.0f);

	CallFunc *callFunc = CallFunc::create(CC_CALLBACK_0(HelloWorld::gotoMenuScene,this));

	c_Sprite->runAction(Sequence::create(c_FadeOut,callFunc,NULL));
}

void HelloWorld::gotoMenuScene()
{
	log("go to MenuScene");
	Director::getInstance()->replaceScene(MenuLayer::createScene());
}