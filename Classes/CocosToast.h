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

	//node����Ӹ�Toast  layer�ĸ��ڵ�;msg����ʾ����Ϣ;time��toast��ʾ��ʱ�䳤��;point��toast��ʾ��λ������
	static void createToast(cocos2d::Node *node,const char *msg,const float &time,cocos2d::Vec2 point);    

	void removeToast(Node *node);
};

#endif