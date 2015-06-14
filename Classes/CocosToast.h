#ifndef __COCOS_TOAST_H__
#define __COCOS_TOAST_H__

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class CocosToast : public cocos2d::LayerColor
{
public:
	CocosToast();
	~CocosToast();

	//node：添加该Toast  layer的父节点;msg：显示的信息;time：toast显示的时间长短;point：toast显示的位置坐标
	static void createToast(cocos2d::Node *node,const char *msg,const float &time,cocos2d::Vec2 point);    

	void removeToast(Node *node);
};

#endif