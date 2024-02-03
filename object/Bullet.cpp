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
	mX = x;
	mY = y;
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
