#pragma once
#include<vector>
#include"object/UI.h"
#include"BaseManager.h"
class CUIMANAGER:public CBASEMANAGER
{
public:
	~CUIMANAGER();
	void Init();
	void Run();
	void End();
	static CUIMANAGER* getInstance();
private:
	CUIMANAGER();
	CUIMANAGER(const CUIMANAGER& that);
	static CUIMANAGER* manager;
	std::vector<CBASEUI*> uiList;
};
