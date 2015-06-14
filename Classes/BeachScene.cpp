#include "BeachScene.h"

USING_NS_CC;

Scene* BeachLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = BeachLayer::create();
	scene->addChild(layer);

	return scene;
}

bool BeachLayer::init()
{
	addMap();
	initTiledGrid();
	initPropTiledID();
	if(!GameBaseLayer::init())
	{
		return false;
	}

	return true;
}

void BeachLayer::addMap()
{
	_map = TMXTiledMap::create( "map/beach.tmx");
	addChild(_map);
	
}

void BeachLayer::initTiledGrid()
{
	tiledColsCount = 22;
	tiledRowsCount = 22;
	canPassGrid = new  bool*[tiledRowsCount];  
	 for(int i=0;i<tiledRowsCount;i++)
	 {
		 canPassGrid[i]=new bool [tiledColsCount];	
	 }	 

	for(int row = 0;row<tiledRowsCount;row++)
	{
		for(int col = 0;col<tiledColsCount;col++)
		{
			canPassGrid[row][col] = false;
		}
	}
	 
}

void BeachLayer::initPropTiledID()
{
	//µØÍ¼µÄTiledID
	blank_land_tiledID   = 1;
	strength_30_tiledID  = 4;
	strength_50_tiledID  = 5;
	strength_80_tiledID  = 6;

	randomEvent_tiledID  = 7;

	player2_building_1_tiledID = 10;
	player2_building_2_tiledID = 11;
	player2_building_3_tiledID = 12;

	player1_building_1_tiledID = 13;
	player1_building_2_tiledID = 14;
	player1_building_3_tiledID = 15;

	
}