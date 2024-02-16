#pragma once
#include"vector"
#include"object/Jet.h"
#include "BaseManager.h"

class CBulletAction;
//·É»ú¹ÜÀíÆ÷
class CJETMANAGER:public CBASEMANAGER
{
public:
	~CJETMANAGER();
	void Init();
	void Run();
	void End();
	static CJETMANAGER* getInstance(CBulletAction*ba);
	void setBA(CBulletAction* ba);
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

