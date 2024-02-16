#pragma once
#include "Rect.h"
#include "path.h"

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
	void Init();
	void Run();
	void End();
};

class EnemyJetNumOne :public CJet {
private:
	int offsetX;
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
	unsigned long long lastMoveTime;
	bool attackFlag;
	bool leftFlag;

public:
	EnemyJetBoss(CBulletAction*);
	~EnemyJetBoss();
	void Init();
	void Run();
	void End();
};
