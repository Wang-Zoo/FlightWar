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
	virtual bool collision(CRect*) = 0;
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
	bool collision(CRect* bulletP);

private:
	unsigned long long lastAddNewEnemyTime;
	static CJETMANAGER* p;
	CBulletAction* mBA;
	int startX;
	bool addFinish;
	CJETMANAGER();
	CJETMANAGER(const CJETMANAGER& that);
	std::vector<CJet*> jets;
};

