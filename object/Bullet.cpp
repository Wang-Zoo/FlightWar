#include "Bullet.h"
#include "tool/Output.h"
#include "tool/config.h"
CBASEBULLET::CBASEBULLET(int x, int y, int w, int h)
{
	mX = x;
	mY = y;

	mRect.SetXY(x, y);
	mRect.SetWH(w, h);

	isDeaded = false;
}

CBASEBULLET::~CBASEBULLET()
{
}

bool CBASEBULLET::isDead()
{
	return isDeaded;
}

void CBASEBULLET::dead()
{
	isDeaded = true;
}

CRect* CBASEBULLET::getRectP()
{
	return &mRect;
}

MyJetBulletNumOne::MyJetBulletNumOne(int x, int y) :CBASEBULLET(x + (MY_JET_WIDTH - MY_BULLET_NUM_ONE_WIDTH) / 2, y - MY_BULLET_NUM_ONE_HEIGHT, MY_BULLET_NUM_ONE_WIDTH, MY_BULLET_NUM_ONE_HEIGHT)
{

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
	mY -= 1.0f;
	if (mY < 0) {
		isDeaded = true;
	}
	mRect.SetXY(mX, mY);
}

void MyJetBulletNumOne::End()
{
}

MyJetBulletNumTwo::MyJetBulletNumTwo() :CBASEBULLET(0, 0, MY_BULLET_NUM_TWO_WIDTH, MY_BULLET_NUM_TWO_HEIGHT)
{
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
	mRect.SetXY(mX, mY);
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

EnemyJetBullet::EnemyJetBullet(int x,int y) :CBASEBULLET(x , y , ENEMY_BULLET_WIDTH, ENEMY_BULLET_HEIGHT)
{
	colorFlag = false;
}

void EnemyJetBullet::Init()
{
	COutput::getInstance()->AddPic(BMP_ENEMY_BULLET, KEY_ENEMY_BULLET_RED_BG, 56, 7, ENEMY_BULLET_WIDTH, ENEMY_BULLET_HEIGHT, RGB(13, 237, 13));
	COutput::getInstance()->AddPic(BMP_ENEMY_BULLET, KEY_ENEMY_BULLET_BLUE_BG, 57, 38, ENEMY_BULLET_WIDTH, ENEMY_BULLET_HEIGHT, RGB(13, 237, 13));
}

void EnemyJetBullet::Run()
{
	unsigned long long curTime = GetTickCount64();
	if (curTime - lastTime > 5) {
		lastTime = curTime;
		colorFlag = !colorFlag;
		mY++;
		if (mY >= _CLIENT_H - ENEMY_BULLET_HEIGHT) {
			isDeaded = true;
		}
	}
	if (!isDeaded) {
		COutput::getInstance()->Draw(colorFlag ? KEY_ENEMY_BULLET_BLUE_BG : KEY_ENEMY_BULLET_RED_BG, mX, mY);
	}
	mRect.SetXY(mX, mY);
}

void EnemyJetBullet::End()
{
}

EnemyBossJetBullet::EnemyBossJetBullet() :CBASEBULLET(100, 500, ENEMY_BOSS_BULLET_WIDTH, ENEMY_BOSS_BULLET_HEIGHT)
{
	
}

void EnemyBossJetBullet::Init()
{
	COutput::getInstance()->AddPic(BMP_ENEMY_BULLET, KEY_ENEMY_BOSS_BULLET_BG, 7, 6, ENEMY_BOSS_BULLET_WIDTH, ENEMY_BOSS_BULLET_HEIGHT, RGB(13, 237, 13));
}

void EnemyBossJetBullet::Run()
{
	COutput::getInstance()->Draw(KEY_ENEMY_BOSS_BULLET_BG, mX, mY);

}

void EnemyBossJetBullet::End()
{
}
