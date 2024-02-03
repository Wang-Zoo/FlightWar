#include "Jet.h"
#include "tool/Output.h"
#include "tool/config.h"
#include "object/Rect.h"

CJet::CJet()
{
	horDir = 0;
}

CJet::~CJet()
{

}     

CMyJet::CMyJet():CJet()
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
	if (GetAsyncKeyState('W')) {
		mY-=step;
		if (mY<0) {
			mY = 0;
		}
	}
	else if (GetAsyncKeyState('S')) {
		mY+=step;
		if (mY > _CLIENT_H - MY_JET_HEIGHT) {
			mY = _CLIENT_H - MY_JET_HEIGHT;
		}
	}
	if (GetAsyncKeyState('A')) {
		horDir = 1;
		mX-=step;
		if (mX < 0) {
			mX = 0;
		}
	}
	else if (GetAsyncKeyState('D')) {
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
