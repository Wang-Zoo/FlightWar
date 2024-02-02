#pragma once
#include "Rect.h"
class CJet
{
public:
	CJet();
	~CJet();
	virtual void Init() = 0;
	virtual void Run() = 0;
	virtual void End() = 0;
protected:
	CRect* rect;
	float mX;
	float mY;
};

class CMyJet:public CJet
{
public:
	CMyJet();
	~CMyJet();

private:
	void Init();
	void Run();
	void End();
};

