#pragma once
#include "vector"
class CBASEMANAGER;
class CSCENE
{
public:
	CSCENE();
	~CSCENE();
	virtual void Init() = 0;
	virtual int Run() = 0;
	virtual void End() = 0;
};

class CStartScene :public CSCENE {
private:
	int startY;
	unsigned long long lastTime;
	int chooseY;
public:
	CStartScene();
	void Init();
	int Run();
	void End();
};

class CNumOneScene :public CSCENE {
private:
	std::vector<CBASEMANAGER*> mList;
public:
	CNumOneScene();
	void Init();
	int Run();
	void End();
};

class CEndScene :public CSCENE {
private:
	int chooseY;
public:
	CEndScene();
	void Init();
	int Run();
	void End();
};