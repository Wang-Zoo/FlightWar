#include "Jet.h"
#include "tool/Output.h"
#include "tool/config.h"
#include "object/Rect.h"
#include "manager/BulletManager.h"
#include "tool/random.h"
CJet::CJet(CBulletAction* ba,int x,int y,int w,int h)
{
	horDir = 0;
	mBulletAction = 0;
	mBulletAction = ba;
	isDeaded = false;
	mX = x;
	mY = y;
	mRectP.SetXY(x,y);
	mRectP.SetWH(w,h);
}

CJet::~CJet()
{

}

bool CJet::collision(CRect* r)
{
	return mRectP.Collision(r);
}

bool CJet::isDead()
{
	return isDeaded;
}

void CJet::dead()
{
	isDeaded = true;
}

bool CJet::canDestory()
{
	return isDeaded&&mBZ.finish();
}

CMyJet::CMyJet(CBulletAction* ba) :CJet(ba, (_CLIENT_W - MY_JET_WIDTH) / 2, (_CLIENT_H - MY_JET_HEIGHT - 50),MY_JET_WIDTH,MY_JET_HEIGHT)
{

}

CMyJet::~CMyJet()
{
}

void CMyJet::Init()
{
	COutput::getInstance()->AddPic(BMP_JET, KEY_MY_JET_IDOL, 1, 0, MY_JET_WIDTH, MY_JET_HEIGHT, RGB(13, 237, 13));
	COutput::getInstance()->AddPic(BMP_JET, KEY_MY_JET_LEFT, 45, 0, MY_JET_LEFT_WIDTH, MY_JET_HEIGHT, RGB(13, 237, 13));
	COutput::getInstance()->AddPic(BMP_JET, KEY_MY_JET_RIGHT, 81, 0, MY_JET_LEFT_WIDTH, MY_JET_HEIGHT, RGB(13, 237, 13));
	step = 0.5f;
}

void CMyJet::Run()
{
	if (isDeaded) {
		mBZ.show(mX,mY,MY_JET_WIDTH,MY_JET_HEIGHT);
		return;
	}
	if (GetAsyncKeyState('J') & 0x8000) {
		unsigned long long curTime = GetTickCount64();
		if (curTime - mLastFireTime > 100) {
			mLastFireTime = curTime;
			mBulletAction->Add(new MyJetBulletNumOne(mX,mY));
		}
	}
	mBulletAction->fireBullet(mX,mY, GetAsyncKeyState('K') & 0x8000);	
	if (GetAsyncKeyState('W') & 0x8000) {
		mY -= step;
		if (mY < 0) {
			mY = 0;
		}
	}
	else if (GetAsyncKeyState('S') & 0x8000) {
		mY += step;
		if (mY > _CLIENT_H - MY_JET_HEIGHT) {
			mY = _CLIENT_H - MY_JET_HEIGHT;
		}
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		horDir = 1;
		mX -= step;
		if (mX < 0) {
			mX = 0;
		}
	}
	else if (GetAsyncKeyState('D') & 0x8000) {
		horDir = 2;
		mX += step;
		if (mX > _CLIENT_W - MY_JET_WIDTH) {
			mX = _CLIENT_W - MY_JET_WIDTH;
		}
	}
	else {
		horDir = 0;
	}
	if (horDir == 0) {
		COutput::getInstance()->Draw(KEY_MY_JET_IDOL, mX, mY);
	}
	else if (horDir == 1) {
		COutput::getInstance()->Draw(KEY_MY_JET_LEFT, mX, mY);
	}
	else if (horDir == 2) {
		COutput::getInstance()->Draw(KEY_MY_JET_RIGHT, mX, mY);
	}
	mRectP.SetXY(mX, mY);
}

void CMyJet::End()
{
}

void EnemyJetNumOne::aiHorMove()
{
	float offset = 0.01f;
	if (horStep == 0) {
		horStep = getIntRange(-20, 20);
	}
	if (horStep < 0) {
		mX-= offset;
		horStep++;
		if (mX < offsetX - 50) {
			mX = offsetX - 50;
		}
	}
	else if (horStep > 0) {
		mX+= offset;
		horStep--;
		if (mX > offsetX + 50) {
			mX = offsetX + 50;
		}
	}
	else {

	}
}

void EnemyJetNumOne::aiVerMove()
{
	float offset = 1.0f;
	if (verStep == 0) {
		verStep = getIntRange(-20, 20);
	}
	if (verStep < 0) {
		mY-= offset;
		verStep++;
		if (mY < 100) {
			mY = 100;
		}
	}
	else if (verStep > 0) {
		mY+= offset;
		verStep--;
		if (mY > 200) {
			mY = 200;
		}
		unsigned long long curTime = GetTickCount64();
		if (curTime - lastAttckTime > 2000) {
			lastAttckTime = curTime;
			//mBulletAction->Add(new EnemyJetBullet(mX, mY+ ENEMY_JET_HEIGHT));
		}
	}
	else {

	}
}

EnemyJetNumOne::EnemyJetNumOne(CBulletAction* ba,int offsetX) :CJet(ba,offsetX,0,ENEMY_JET_WIDTH,ENEMY_JET_HEIGHT)
{
	this->offsetX = offsetX;
	leftDir = false;
	upDir = false;
	horStep = 0;
	verStep = 0;
	lastAttckTime = GetTickCount64();
	lastTime = GetTickCount64();

	{
		CPOS pos(offsetX, 0);
		path.add(pos);
	}

	{
		CPOS pos(offsetX, 400);
		path.add(pos);
	}

	{
		CPOS pos(offsetX + 50, 400);
		path.add(pos);
	}

	{
		CPOS pos(offsetX + 50, 100);
		path.add(pos);
	}
}

EnemyJetNumOne::~EnemyJetNumOne()
{

}

void EnemyJetNumOne::Init()
{
	COutput::getInstance()->AddPic(BMP_ENEMY_JET, KEY_ENEMY_JET_UP, 6, 8, ENEMY_JET_WIDTH, ENEMY_JET_HEIGHT, RGB(13, 237, 13));
	COutput::getInstance()->AddPic(BMP_ENEMY_JET, KEY_ENEMY_JET_DOWN, 73, 8, ENEMY_JET_WIDTH, ENEMY_JET_HEIGHT, RGB(13, 237, 13));
}

void EnemyJetNumOne::Run()  
{
	if (isDeaded) {
		mBZ.show(mX, mY,ENEMY_JET_WIDTH, ENEMY_JET_HEIGHT);
		return;
	}

	if (!path.finish()) {
		upDir = path.calculatePos(&mX, &mY);
	}
	else {
		unsigned long long curTime = GetTickCount64();

		if (curTime - lastTime > 10) {
			lastTime = curTime;
			aiHorMove();
			aiVerMove();
			upDir = verStep < 0;
		}

	}
	COutput::getInstance()->Draw(upDir?KEY_ENEMY_JET_UP: KEY_ENEMY_JET_DOWN, mX, mY);
	mRectP.SetXY(mX, mY);
}

void EnemyJetNumOne::End()
{

}

EnemyJetBoss::EnemyJetBoss(CBulletAction* ba):CJet(ba,300,100,ENEMY_BOSS_JET_WIDTH,ENEMY_BOSS_JET_HEIGHT)
{
	
}

EnemyJetBoss::~EnemyJetBoss()
{
}

void EnemyJetBoss::Init()
{
	attackFlag = false;
	leftFlag = false;
	lastAttackTime = GetTickCount64();
	COutput::getInstance()->AddPic(BMP_BOSS_ENEMY_JET, KEY_ENEMY_BOSS_JET_CLOSE, 41, 30, ENEMY_BOSS_JET_WIDTH, ENEMY_BOSS_JET_HEIGHT, RGB(13, 237, 13));
	COutput::getInstance()->AddPic(BMP_BOSS_ENEMY_JET, KEY_ENEMY_BOSS_JET_OPEN, 237, 25, ENEMY_BOSS_JET_WIDTH, ENEMY_BOSS_JET_HEIGHT, RGB(13, 237, 13));
}

void EnemyJetBoss::Run()
{
	unsigned long long curTime = GetTickCount64();
	if (curTime - lastAttackTime > 5000) {
		attackFlag = !attackFlag;
		lastAttackTime = curTime;
	} 
	if (curTime - lastMoveTime > 10) {
		lastMoveTime = curTime;
		if (mX > 400) {
			leftFlag = true;
		}
		else if (mX < 200) {
			leftFlag = false;
		}
		if (leftFlag) {
			mX--;
		}
		else {
			mX++;
		}
	}
	COutput::getInstance()->Draw(attackFlag?KEY_ENEMY_BOSS_JET_OPEN: KEY_ENEMY_BOSS_JET_CLOSE, mX, mY);
	mRectP.SetXY(mX, mY);
}

void EnemyJetBoss::End()
{
}
