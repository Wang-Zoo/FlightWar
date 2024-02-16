#include "JetManager.h"
#include "tool/Output.h"
#include "tool/config.h"
#include "object/Jet.h"
#include "BulletManager.h"
CJETMANAGER* CJETMANAGER::p = 0;

CJETMANAGER* CJETMANAGER::getInstance()
{
	if (!p) {
		p = new CJETMANAGER();
	}
	return p;
}

void CJETMANAGER::setBA(CBulletAction* ba)
{
	this->mBA = ba;
}

bool CJETMANAGER::collision(CRect* bulletP,bool isEnemy)
{
	for (auto temp : jets)
	{
		if (temp->isDead()) {
			continue;
		}
		if (dynamic_cast<CMyJet*>(temp)&&!isEnemy) {
			continue;
		}

		bool collision = temp->collision(bulletP);
		if (collision) {
			temp->dead();
			return true;
		}
	}
	return false;
}


void CJETMANAGER::Add(CJet* jet)
{
	jet->Init();
	jets.push_back(jet);
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
	addFinish = false;
	startX = 500;
	Add(new CMyJet(mBA));
	Add(new EnemyJetBoss(mBA));
}

void CJETMANAGER::Run()
{
	auto it = jets.begin();
	for (;it!=jets.end();)
	{
		if ((*it)->canDestory()) {
			delete(*it);
			it = jets.erase(it);
		}
		else {
			(*it)->Run();
			it++;
		}
	}
	unsigned long long curTime = GetTickCount64();
	if (!addFinish&&curTime - lastAddNewEnemyTime > 1000) {
		lastAddNewEnemyTime = curTime;
		Add(new EnemyJetNumOne(mBA, startX));
		startX -= 150;
		if (startX <= 100) {
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

CJetAction::CJetAction()
{
}

CJetAction::~CJetAction()
{
}
