#pragma once
#include "Rect.h"
#include "baozha.h"
class CBASEBULLET
{
public:
	CBASEBULLET(int x, int y, int w, int h);
	~CBASEBULLET();
	virtual void Init() = 0;
	virtual void Run() = 0;
	virtual void End() = 0;
	bool isDead();
	void dead();
	bool canDestory();
	CMyRect* getRectP();
protected:
	CBZ mBZ;
	CMyRect mRect;
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
	unsigned long long mLastSmallTime;
	bool smallFlag;
public:
	MyJetBulletNumTwo();
	void Init();
	void Run();
	void End();
	void setXY(int x, int y);
	void fire(int x,int y);
};

class EnemyJetBullet :public CBASEBULLET {
private:
	bool colorFlag;
	unsigned long long lastTime;
public:
	EnemyJetBullet(int x,int y);
	void Init();
	void Run();
	void End();
};

class EnemyBossJetBullet :public CBASEBULLET {
private:

public:
	EnemyBossJetBullet(int x,int y);
	void Init();
	void Run();
	void End();
};