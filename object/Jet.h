#pragma once
#include "Rect.h"
#include "path.h"
#include "baozha.h"

class CBulletAction;

class CJet
{
public:
	CJet(CBulletAction* ba, int x, int y, int w, int h);
	~CJet();
	virtual void Init() = 0;
	virtual void Run() = 0;
	virtual void End() = 0;
	bool collision(CMyRect* r);
	bool isDead();
	void dead(float damage = 1.0f);
	bool canDestory();
protected:
	bool wudi;
	float hp;
	CBZ mBZ;
	CMyRect mRectP;
	float mX;
	float mY;
	float step;
	int horDir;
	bool isDeaded;
	CBulletAction* mBulletAction;
	unsigned long long mLastFireTime;
};

class CMyJet:public CJet
{
public:
	CMyJet(CBulletAction* );
	~CMyJet();
	void Init();
	void Run();
	void End();
};

class EnemyJetNumOne :public CJet {
private:
	float offsetX;
	bool leftDir;
	bool upDir;
	int horStep;
	int verStep;
	CMOVEPATH path;
	unsigned long long lastTime;
	unsigned long long lastAttckTime;
	void aiHorMove();
	void aiVerMove();
public:
	EnemyJetNumOne(CBulletAction*,int);
	~EnemyJetNumOne();
	void Init();
	void Run();
	void End();
};

class EnemyJetBoss :public CJet {
private:
	unsigned long long lastAttackTime;
	unsigned long long lastFireTime;
	unsigned long long lastMoveTime;
	bool attackFlag;
	bool leftFlag;
	CMOVEPATH path;

public:
	EnemyJetBoss(CBulletAction*);
	~EnemyJetBoss();
	void Init();
	void Run();
	void End();
};
