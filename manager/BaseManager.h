#pragma once
class CBASEMANAGER
{
public:
	CBASEMANAGER();
	virtual ~CBASEMANAGER();
	virtual void Init() = 0;
	virtual bool Run() = 0;
	virtual void End() = 0;
};
