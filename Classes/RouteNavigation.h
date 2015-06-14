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
	static RouteNavigation *routeNav_Instance;    //��̬����
	static RouteNavigation *getInstance();        //��̬�����ȡ����
	void getPath(RicherPlayer *player,int stepsCount,bool **canPassGrid,int gridRowsCount,int gridColsCount);
	bool isCanGoByRowCol(int row,int col,int direction,bool **canPassGrid);//�жϸ÷����Ƿ�����
private:
	RouteNavigation();
	~RouteNavigation();
		
	CC_SYNTHESIZE(std::vector<int>,pathCols_vector,PathCols_vector);    //��¼�¼���·�ߵ��к�
	CC_SYNTHESIZE(std::vector<int>,pathRows_vector,PathRows_vector);    //��¼�¼���·�ߵ��к�

};

#endif