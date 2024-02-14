#include "Bullet.h"
#include "tool/Output.h"
#include "tool/config.h"
CBASEBULLET::CBASEBULLET()
{
	isDeaded = false;
}

CBASEBULLET::~CBASEBULLET()
{
}

bool CBASEBULLET::isDead()
{
	return isDeaded;
}

MyJetBulletNumOne::MyJetBulletNumOne(int x, int y) :CBASEBULLET()
{
	mX = x + (MY_JET_WIDTH - MY_BULLET_NUM_ONE_WIDTH) / 2;
	mY = y - MY_BULLET_NUM_ONE_HEIGHT;
}

void MyJetBulletNumOne::Init()
{
	COutput::getInstance()->AddPic(BMP_BULLET, KEY_MY_BULLET_ONE_BG, 1, 1, MY_BULLET_NUM_ONE_WIDTH, MY_BULLET_NUM_ONE_HEIGHT, RGB(13, 237, 13));
}

void MyJetBulletNumOne::Run()
{
	if (isDeaded) {
		return;
	}
	COutput::getInstance()->Draw(KEY_MY_BULLET_ONE_BG, mX, mY);
	mY -= 1;
	if (mY < 0) {
		isDeaded = true;
	}
}

void MyJetBulletNumOne::End()
{
}

MyJetBulletNumTwo::MyJetBulletNumTwo()
{
	mX = 0;
	mY = 0;
	targetW = MY_BULLET_NUM_TWO_WIDTH;
	targetH = 0;
	accFlag = false;
}

void MyJetBulletNumTwo::Init()
{
	COutput::getInstance()->AddPic(BMP_FIRE_BULLET, KEY_MY_BULLET_TWO_BG, 9, 0, MY_BULLET_NUM_TWO_WIDTH, MY_BULLET_NUM_TWO_HEIGHT, RGB(13, 237, 13));
}

void MyJetBulletNumTwo::Run()
{
	if (isDeaded) {
		return;
	}
	COutput::getInstance()->Draw(KEY_MY_BULLET_TWO_BG, mX, mY, targetW, targetH);

	unsigned long long curTime = GetTickCount64();
	if (curTime - mLastFireTime > 50) {
		accFlag = false;
	}
	if (!accFlag) {
		targetH--;
		if (targetH <= 0) {
			targetH = 0;
			mX = 0 - MY_BULLET_NUM_TWO_WIDTH;
		}
	}
}

void MyJetBulletNumTwo::End()
{

}

void MyJetBulletNumTwo::setXY(int x, int y)
{
	mX = x + (MY_JET_WIDTH - MY_BULLET_NUM_TWO_WIDTH) / 2;
	mY = y - targetH;
}

void MyJetBulletNumTwo::fire(int x, int y)
{
	targetH++;
	if (targetH >= MY_BULLET_NUM_TWO_HEIGHT) {
		targetH = MY_BULLET_NUM_TWO_HEIGHT;
	}
	mLastFireTime = GetTickCount64();
	accFlag = true;
	setXY(x, y);
}
