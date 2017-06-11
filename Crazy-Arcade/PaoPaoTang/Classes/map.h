/**********************/
/*
*文件说明：此文件包含游戏中瓦片地图创建及其坐标相关函数的声明
*作者：陈乾
*时间：2017-6-2
*/
/**********************/

#ifndef _MAP_H_
#define _MAP_H_

#include "cocos2d.h"


class CMap :public cocos2d::CCTMXTiledMap
{
public:
	static CMap* initTileMap(const char* tmxFile);

	//通过指定坐标转换为地图块坐标
	cocos2d::CCPoint tilePosFromLocation(cocos2d::CCPoint pos);
	//判断瓦片是否为障碍
	bool isTilePosBlocked(cocos2d::CCPoint pos);
	bool bombBlock[20][15];
	void setBombBlock(int x, int y,bool z);
};


#endif // !_MAP_H_
