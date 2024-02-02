#pragma once
#include<vector>
#include"object/UI.h"

class CUIMANAGER
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
