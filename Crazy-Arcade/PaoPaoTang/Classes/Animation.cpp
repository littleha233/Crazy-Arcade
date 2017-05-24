#include"Animation.h"
using namespace cocos2d;
using namespace std;


SngPic AniSettingDate;
fstream inFile("AniSettingDate.txt", ios::in | ios::out);
void loadAni()
{
	char tempCh = '0';
	string tempStr;
	while (!inFile.eof())
	{
		inFile >> AniSettingDate.filename;
		inFile >> AniSettingDate.picWidth;
		inFile >> AniSettingDate.picHeight;
		inFile >> AniSettingDate.divideWidth;
		inFile >> AniSettingDate.divideHeight;
		inFile >> AniSettingDate.order;
		tempCh = '0' + AniSettingDate.order;
		tempStr=AniSettingDate.filename;
		load(AniSettingDate, tempCh, tempStr);
		
	}
	
	inFile.close();

}

void load(SngPic& sp,char tempCh, string tempStr)
{
	CCAnimation* animation =  CCAnimation::create();
	for (int i = 0; i < sp.divideWidth; i++)
		animation->addSpriteFrameWithTexture(CCTextureCache::sharedTextureCache()->addImage(sp.filename),
			CCRectMake(i * sp.picWidth / sp.divideWidth, sp.order * sp.picHeight / sp.divideHeight, sp.picWidth / sp.divideWidth, sp.picHeight / sp.divideHeight));
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(1.0 / 6.0);
	animation->setLoops(-1);
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation, (tempStr + tempCh).c_str());
}



