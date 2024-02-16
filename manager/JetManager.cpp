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
	COutput::getInstance()->AddBmp(BMP_ENEMY_JET_PATH, BMP_ENEMY_JET);
	COutput::getInstance()->AddBmp(BMP_ENEMY_BOSS_JET_PATH, BMP_BOSS_ENEMY_JET);
	jets.push_back(new CMyJet(mBA));
	for (auto temp : jets)
	{
		temp->Init();
	}
	addFinish = false;
	startX = 500;
}

void CJETMANAGER::Run()
{
	for (auto temp : jets)
	{
		temp->Run();
	}
	unsigned long long curTime = GetTickCount64();
	if (!addFinish&&curTime - lastAddNewEnemyTime > 1000) {
		lastAddNewEnemyTime = curTime;
		EnemyJetNumOne* temp = new EnemyJetNumOne(mBA, startX);
		temp->Init();
		jets.push_back(temp);
		startX -= 100;
		if (startX <= 0) {
			addFinish = true;
		}
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
