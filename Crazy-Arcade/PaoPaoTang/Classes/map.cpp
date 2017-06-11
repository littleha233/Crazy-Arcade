/**********************/
/*
*文件说明：此文件包含游戏中瓦片地图创建及其坐标相关函数的定义
*作者：陈乾
*时间：2017-6-2
*/
/**********************/
#include "map.h"
#include "bomb.h"
using namespace cocos2d;
class CBomb;
CMap* CMap::initTileMap(const char *tmxfile)
{
	CMap *map = new CMap;
	memset(map->bombBlock, 0, sizeof(map->bombBlock));
	if (map->initWithTMXFile(tmxfile))
	{
		CCTMXLayer *clayer = map->layerNamed("collision");       //通过层名字获得该层对象  
		//clayer->setVisible(false);
		map->autorelease();
		return map;
	}

	CC_SAFE_DELETE(map);
	return NULL;
}

//通过指定的坐标转换为地图块坐标  
CCPoint CMap::tilePosFromLocation(CCPoint pos)
{
	int x = pos.x / this->getTileSize().width;
	int y = pos.y / this->getTileSize().height;

	y = this->getMapSize().height - y-1;
	return ccp(x, y);
}
//判断该瓦片是否为障碍  
bool CMap::isTilePosBlocked(CCPoint pos)
{
	//判断当前块是否为碰撞块  
	CCPoint tilpos = tilePosFromLocation(pos);                //将带入的坐标转为块坐标  
	CCTMXLayer *clayer = this->layerNamed("collision");      //通过层名字获得该层对象 


	int tileGID = clayer->tileGIDAt(tilpos);             //获得该块的GID标识别  
	if (tileGID != 0)
	{
		CCDictionary* properties = this->propertiesForGID(tileGID);
		if (strcmp(properties->valueForKey("Collidable")->getCString(), "true") == 0)
			return true;
	}
	if (bombBlock[(int)tilpos.x][(int)tilpos.y])
		return true;

	return false;
}

void CMap::setBombBlock(int x, int y,bool z)
{
	bombBlock[x][y] = z;
}


