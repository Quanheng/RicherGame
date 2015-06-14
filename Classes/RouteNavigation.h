#ifndef __ROUTE_NAVIGATION_H__
#define __ROUTE_NAVIGATION_H__

#include "cocos2d.h"
#include "GameBaseScene.h"
#include "RicherPlayer.h"

USING_NS_CC;

const int GO_UP = 0;
const int GO_DOWN =1;
const int GO_LEFT =2;
const int GO_RIGHT =3;

class RouteNavigation
{
public:
	static RouteNavigation *routeNav_Instance;    //静态对象
	static RouteNavigation *getInstance();        //静态对象获取方法
	void getPath(RicherPlayer *player,int stepsCount,bool **canPassGrid,int gridRowsCount,int gridColsCount);
	bool isCanGoByRowCol(int row,int col,int direction,bool **canPassGrid);//判断该方向是否能走
private:
	RouteNavigation();
	~RouteNavigation();
		
	CC_SYNTHESIZE(std::vector<int>,pathCols_vector,PathCols_vector);    //记录下几步路线的列号
	CC_SYNTHESIZE(std::vector<int>,pathRows_vector,PathRows_vector);    //记录下几步路线的行号

};

#endif