#include "SeaScene.h"

USING_NS_CC;

Scene* SeaLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = SeaLayer::create();
	scene->addChild(layer);

	return scene;
}

bool SeaLayer::init()
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

void SeaLayer::addMap()
{
	_map = TMXTiledMap::create("map/sea.tmx");
	this->addChild(_map);
}

void SeaLayer::initTiledGrid()
{
	tiledColsCount = 20;
	tiledRowsCount = 15;

	canPassGrid = new bool *[tiledRowsCount];
	for(int i=0;i<tiledRowsCount;i++)
	{
		canPassGrid[i] = new bool[tiledColsCount];
	}
	for(int row =0;row < tiledRowsCount ;row++)
	{
		for(int col = 0;col < tiledColsCount; col++)
		{
			canPassGrid[row][col] = false;
		}
	}
}

void SeaLayer::initPropTiledID()
{
	//��ͼ��TiledID
	blank_land_tiledID   = 1;     //�յ�

    strength_30_tiledID  = 4;     //+30�����ĵ�ͼ��
	strength_50_tiledID  = 5;
	strength_80_tiledID  = 6;

	randomEvent_tiledID  = 7;    //�ʺ��¼�

	player2_building_1_tiledID = 10;    //��ɫ2��1������
	player2_building_2_tiledID = 11;
	player2_building_3_tiledID = 12;

	player1_building_1_tiledID = 13;
	player1_building_2_tiledID = 14;
	player1_building_3_tiledID = 15;
	
}