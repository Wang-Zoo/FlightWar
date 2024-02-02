#include "JetManager.h"
#include "tool/Output.h"
#include "tool/config.h"
#include "object/Jet.h"

CJETMANAGER* CJETMANAGER::p = 0;

CJETMANAGER* CJETMANAGER::getInstance()
{
	if (!p) {
		p = new CJETMANAGER;
	}
	return p;
}

CJETMANAGER::CJETMANAGER()
{
}

CJETMANAGER::~CJETMANAGER()
{
}

void CJETMANAGER::Init()
{
	COutput::getInstance()->AddBmp(BMP_JET_PATH, BMP_JET);
	jets.push_back(new CMyJet);
	for (auto temp : jets)
	{
		temp->Init();
	}
}

void CJETMANAGER::Run()
{
	for (auto temp : jets)
	{
		temp->Run();
	}
}

void CJETMANAGER::End()
{
	for (auto temp : jets)
	{
		temp->End();
		delete temp;
	}
}
