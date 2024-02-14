#pragma once
#include "Rect.h"
class CBASEBULLET
{
public:
	CBASEBULLET();
	~CBASEBULLET();
	virtual void Init() = 0;
	virtual void Run() = 0;
	virtual void End() = 0;
	bool isDead();
protected:
	CRect mRect;
	float mX;
	float mY;
	bool isDeaded;
};

class MyJetBulletNumOne :public CBASEBULLET {
public:
	MyJetBulletNumOne(int x,int y);
	void Init();
	void Run();
	void End();
};

class MyJetBulletNumTwo :public CBASEBULLET {
private:
	int targetW;
	int targetH;
	bool accFlag;
	unsigned long long mLastFireTime;
public:
	MyJetBulletNumTwo();
	void Init();
	void Run();
	void End();
	void setXY(int x, int y);
	void fire(int x,int y);
};