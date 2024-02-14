#include "Jet.h"
#include "tool/Output.h"
#include "tool/config.h"
#include "object/Rect.h"
#include "manager/BulletManager.h"

CJet::CJet(CBulletAction* ba)
{
	horDir = 0;
	mBulletAction = 0;
	mBulletAction = ba;
}

CJet::~CJet()
{

}     

CMyJet::CMyJet(CBulletAction* ba):CJet(ba)
{
	mX = (_CLIENT_W - MY_JET_WIDTH) / 2;
	mY = (_CLIENT_H - MY_JET_HEIGHT - 50);
	
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
	if (GetAsyncKeyState('J') & 0x8000) {
		unsigned long long curTime = GetTickCount64();
		if (curTime - mLastFireTime > 100) {
			mLastFireTime = curTime;
			mBulletAction->Add(new MyJetBulletNumOne(mX + (MY_JET_WIDTH - MY_BULLET_NUM_ONE_WIDTH) / 2, mY - MY_BULLET_NUM_ONE_HEIGHT));
		}
	}
	if (GetAsyncKeyState('W') & 0x8000) {
		mY-=step;
		if (mY<0) {
			mY = 0;
		}
	}
	else if (GetAsyncKeyState('S') & 0x8000) {
		mY+=step;
		if (mY > _CLIENT_H - MY_JET_HEIGHT) {
			mY = _CLIENT_H - MY_JET_HEIGHT;
		}
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		horDir = 1;
		mX-=step;
		if (mX < 0) {
			mX = 0;
		}
	}
	else if (GetAsyncKeyState('D') & 0x8000) {
		horDir = 2;
		mX+= step;
		if (mX > _CLIENT_W-MY_JET_WIDTH) {
			mX = _CLIENT_W - MY_JET_WIDTH;
		}
	}
	else {
		horDir =  0;
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
}

void CMyJet::End()
{
}
