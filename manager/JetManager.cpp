#include "JetManager.h"
#include "tool/Output.h"
#include "tool/config.h"
#include "object/Jet.h"
#include "BulletManager.h"
CJETMANAGER* CJETMANAGER::p = 0;

CJETMANAGER* CJETMANAGER::getInstance(CBulletAction* ba)
{
	if (!p) {
		p = new CJETMANAGER();
		p->setBA(ba);
	}
	return p;
}

void CJETMANAGER::setBA(CBulletAction* ba)
{
	this->mBA = ba;
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
	jets.push_back(new CMyJet(mBA));
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
