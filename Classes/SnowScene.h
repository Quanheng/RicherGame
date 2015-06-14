#ifndef __SNOW_SCENE_H__
#define __SNOW_SCENE_H__

#include "cocos2d.h"
#include "GameBaseScene.h"
#include "ConstUtil.h"

class SnowLayer : public GameBaseLayer
{
public:
	static cocos2d::Scene *createScene();
	virtual bool init();
	void addMap();
    void initTiledGrid();
	void initPropTiledID();
	CREATE_FUNC(SnowLayer);
};

#endif