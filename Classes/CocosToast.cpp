#include "CocosToast.h"

CocosToast::CocosToast()
{

}

CocosToast::~CocosToast()
{
}

void CocosToast::createToast(Node *node,const char *msg,const float &time,Vec2 point)
{
	//������ʾ��Ϣ��label
	auto label = Label::createWithSystemFont(msg,"Arial",20);
	label->setColor(Color3B::WHITE);
	label->ignoreAnchorPointForPosition(false);   
	label->setAnchorPoint(Vec2(0.5,0.5));

	//toast��layer��
	auto layer = LayerColor::create(Color4B(100,100,100,255));
	layer->ignoreAnchorPointForPosition(false);
	layer->setAnchorPoint(Vec2(0.5,0.5));
	layer->setContentSize(label->getContentSize() + Size(20,15));

	node->addChild(layer);
	node->addChild(label);
	layer->setPosition(point);
	label->setPosition(layer->getPosition());
	
	//toast��ʾʱ�Ķ����������¶��ϣ������϶��£��ص�pointλ�ã�������������toast�Ӹ��ڵ����
	auto seq1 = Sequence::create(
		FadeIn::create(time/5),
		DelayTime::create(time/5*1.5),
		FadeOut::create(time/5*2.5),
		CallFuncN::create(layer,callfuncN_selector(CocosToast::removeToast)),
		NULL);
	auto seq2 = Sequence::create(
		EaseSineIn::create(MoveBy::create(time/5,Vec2(0,50))),
		DelayTime::create(time/5*2),
		EaseSineOut::create(MoveBy::create(time/5*3,Vec2(0,-50))),
		NULL);
	auto spawn = Spawn::create(seq1,seq2,NULL);
	auto action = Repeat::create(spawn,1);
	
	layer->setOpacity(0);   //����͸����
	label->setOpacity(0);
	layer->runAction(action);
	label->runAction(action->clone());
	
}

void CocosToast::removeToast(Node *node)
{
	this->removeFromParentAndCleanup(true);
}