#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Richer");
        director->setOpenGLView(glview);
    }

	glview->setDesignResolutionSize(800, 480, ResolutionPolicy::EXACT_FIT); 
    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

	//初始化背景音乐
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG01_MP3);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG02_MP3);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG03_MP3);

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(PARTICLE_EFFECT);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(WALK_MP3);

    //初始化音效
    SimpleAudioEngine::getInstance()->preloadEffect(BUTTON_CLICK);
	SimpleAudioEngine::getInstance()->preloadEffect(BUTTON_CLICK_01);
	SimpleAudioEngine::getInstance()->preloadEffect(STORM_EFFECT);
	SimpleAudioEngine::getInstance()->preloadEffect(BLOCK_THE_WAY);
	SimpleAudioEngine::getInstance()->preloadEffect(STORM_SPEAKING);
	//交过路费声音
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00435);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00461);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00475);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_01060);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_01062);
	//抢夺别人地块
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00429);
	//房屋被抢夺
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00430);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00464);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00469);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00470);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00476);
	//房屋被摧毁
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00462);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00463);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00466);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00468);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00474);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_01061);
	//摧毁别人房屋
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00433);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00437);
	//收取过路费
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00453);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_01059);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_01057);
	//升级房子
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_01051);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_01066);
	//买地
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00458);
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_01067);
	//对方被罚收税
	SimpleAudioEngine::getInstance()->preloadEffect(P1_Speaking_00452);

	//交过路费声音
	SimpleAudioEngine::getInstance()->preloadEffect(P2_SPEAKING01);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_QISIWOLE);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_XINHAOKONGA);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_BUHUIBA);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_PAYHIGH);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_QIANGQIANA);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_HEBAOCHUXIE);
	//抢夺别人地块
	SimpleAudioEngine::getInstance()->preloadEffect(P2_BIEGUAIWO);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_SPEAKING02);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_TIGER);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_NIDEJIUSHODE);
	//房屋被抢夺
	SimpleAudioEngine::getInstance()->preloadEffect(P2_ZHENMIANMU);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_WODEDIQI);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_HAOQIFU);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_WANGFA);
	//摧毁别人房屋
	SimpleAudioEngine::getInstance()->preloadEffect(P2_NIGAIWOCHAI);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_KANWODE);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_HAIRENLE);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_BAOCHOU);
	//房屋被摧毁
	SimpleAudioEngine::getInstance()->preloadEffect(P2_WODEYANGFANG);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_QIFURENJIA);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_SHAQIANDAO);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_LIANXIANGXIYU);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_HAOJIUGAIHAO);
	//收取过路费
	SimpleAudioEngine::getInstance()->preloadEffect(P2_RENBUWEIJI);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_XIAOQI);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_RONGXING);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_MANYI);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_XIAOFUPO);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_DUOGEI);
	//升级房子
	SimpleAudioEngine::getInstance()->preloadEffect(P2_HIGHER);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_WANZHANGGAOLOU);
	//买地
	SimpleAudioEngine::getInstance()->preloadEffect(P2_BUYIT);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_HAODEKAISHI);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_RANGNIZHU);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_MAIWOBA);
	//对方被罚收税
	SimpleAudioEngine::getInstance()->preloadEffect(P2_TOUSHUI);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_FALVZHICAI);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_GUOKU);
	SimpleAudioEngine::getInstance()->preloadEffect(P2_NASHUI);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
