#pragma once
#include"vector"
#include"object/Jet.h"
#include "BaseManager.h"

class CBulletAction;

class CJetAction
{
public:
	CJetAction();
	~CJetAction();
	virtual bool collision(CRect*,bool) = 0;
};

//·É»ú¹ÜÀíÆ÷
class CJETMANAGER:public CBASEMANAGER,public CJetAction
{
public:
	~CJETMANAGER();
	void Init();
	void Run();
	void End();
	static CJETMANAGER* getInstance();
	void setBA(CBulletAction* ba);
	bool collision(CRect* bulletP,bool isEnemy);

private:
	unsigned long long lastAddNewEnemyTime;
	static CJETMANAGER* p;
	CBulletAction* mBA;
	int startX;
	int normalEenmyCount;
	bool addFinish;
	void Add(CJet*);
	CJETMANAGER();
	CJETMANAGER(const CJETMANAGER& that);
	std::vector<CJet*> jets;
};

