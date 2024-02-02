#pragma once
#include"vector"
#include"object/Jet.h"
#include "BaseManager.h"
//·É»ú¹ÜÀíÆ÷
class CJETMANAGER:public CBASEMANAGER
{
public:
	~CJETMANAGER();
	void Init();
	void Run();
	void End();
	static CJETMANAGER* getInstance();
private:
	static CJETMANAGER* p;
	CJETMANAGER();
	CJETMANAGER(const CJETMANAGER& that);
	std::vector<CJet*> jets;
};

