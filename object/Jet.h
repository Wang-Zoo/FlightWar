#pragma once
#include "Rect.h"

class CBulletAction;

class CJet
{
public:
	CJet(CBulletAction* ba);
	~CJet();
	virtual void Init() = 0;
	virtual void Run() = 0;
	virtual void End() = 0;
protected:
	CRect mRectP;
	float mX;
	float mY;
	float step;
	int horDir;
	CBulletAction* mBulletAction;
	unsigned long long mLastFireTime;
};

class CMyJet:public CJet
{
public:
	CMyJet(CBulletAction* );
	~CMyJet();

private:
	void Init();
	void Run();
	void End();
};

