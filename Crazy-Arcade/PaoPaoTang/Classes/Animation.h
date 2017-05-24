/************************************************************************/
/* 作者：陈乾
 *日期：2017-5-24 19:00
 *说明：此文件提供能将所有动画以名称加载入动画池的接口loadAni
 */
/************************************************************************/

#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include"cocos2d.h"
#include<fstream>
#include<string>
#include<memory>
#include<vector>
#include<map>
using namespace cocos2d;
using namespace std;

//记录动画数据的结构体
struct SngPic
{
	char filename[50];
	float picWidth;
	float picHeight;
	int divideWidth;
	int divideHeight;
	int order;
};

extern SngPic AniSettingDate;
extern fstream inFile;

//将单个动画加入动画池，请勿手动调用
void load(SngPic& sp, char ,string);

//加载所以动画，播放动画前需启用，且只需调用一次
void loadAni();


#endif // !_ANIMATION_H_



