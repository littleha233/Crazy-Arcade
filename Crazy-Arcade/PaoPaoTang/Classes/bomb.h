/******************************/
/*文件说明：泡泡类的声明
*作者：陈乾
*日期：2017-6-10
*/
/******************************/

#ifndef _BOMB_H_
#define _BOMB_H_

#include "cocos2d.h"
#include "player.h"

class CPlayer;
class CMap;
class CBomb :public cocos2d::CCNode
{
public:
	CBomb(cocos2d::CCPoint pos, CMap* layer,CPlayer*);
	static CBomb* create(cocos2d::CCPoint pos, CMap* layer,CPlayer*);//初始化泡泡类
	void erase();//清除动画和动作
	void explode(float);//泡泡爆炸
	int expoldeBlock();//泡泡水柱阻挡判断
	~CBomb();

private:
	bool isInBorder(cocos2d::CCPoint);//判断泡泡水柱范围是否在地图内
	void deleteTile(cocos2d::CCPoint pos);//炸毁阻碍并删除瓦片
	cocos2d::CCPoint toTiledPos(cocos2d::CCPoint&);//将泡泡位置放在瓦片中央
	cocos2d::CCSprite* m_sprite;//泡泡及爆炸中心精灵
	cocos2d::CCAnimate* m_ani;//泡泡动画
	cocos2d::CCAction* m_act;//泡泡动作
	CMap* m_pCurMap;//泡泡所在地图
	cocos2d::CCSprite* up;//向上水柱精灵
	cocos2d::CCSprite* down;//...
	cocos2d::CCSprite* left;
	cocos2d::CCSprite* right;
	cocos2d::CCSprite* centre;
	CPlayer* m_pHero;//泡泡所属角色
	cocos2d::CCPoint m_settedPos;//放置泡泡时角色的坐标
	int iUp;
	int iDown;
	int iLeft;
	int iRight;
	
};

#endif // !_BOMB_H_

