#pragma once
#include "Rect.h"
class CBASEUI
{
public:
	CBASEUI();
	~CBASEUI();
	virtual void Init() = 0;
	virtual void Run() = 0;
	virtual void End() = 0;

protected:
	CMyRect* rect;
};

class  BACKGROUND:public CBASEUI
{
public:
	 BACKGROUND();
	~ BACKGROUND();
	void Init();
	void Run();
	void End();
private:
	float moveY = 0.0f;
};
