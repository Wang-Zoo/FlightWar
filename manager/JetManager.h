#pragma once
#include"vector"
#include"object/Jet.h"

//·É»ú¹ÜÀíÆ÷
class CJETMANAGER
{
public:
	CJETMANAGER();
	~CJETMANAGER();
	void Init();
	void Run();
	void End();
private:
	std::vector<CJet> jets;
};

