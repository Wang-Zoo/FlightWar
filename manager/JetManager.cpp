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

bool CJETMANAGER::collision(CMyRect* bulletP,bool isEnemy,float damage)
{
	for (auto temp : jets)
	{
		if (temp->isDead()) {
			continue;
		}
		if (dynamic_cast<CMyJet*>(temp)&&!isEnemy) {
			continue;
		}
		if (dynamic_cast<EnemyJetNumOne*>(temp) && isEnemy) {
			continue;
		}
		if (dynamic_cast<EnemyJetBoss*>(temp) && isEnemy) {
			continue;
		}

		bool collision = temp->collision(bulletP);
		if (collision) {
			temp->dead(damage);
			return true;
		}
	}
	return false;
}

bool CJETMANAGER::stop()
{
	if (normalEenmyCount < 0) {
		int normalEnemy = 0;
		for (auto temp : jets) {
			if (!dynamic_cast<CMyJet*>(temp)) {
				normalEnemy++;
			}
		}
		return !normalEnemy;
	}
	else {
		return false;
	}
}


void CJETMANAGER::Add(CJet* jet)
{
	jet->Init();
	jets.push_back(jet);
}

void CJETMANAGER::AddNormalEnemy()
{
	int normalEnemy = 0;
	for (auto temp : jets) {
		if (dynamic_cast<EnemyJetNumOne*>(temp)) {
			normalEnemy++;
		}
	}
	if (normalEnemy == 0) {
		if (normalEenmyCount > 0&& startX<=100) {
			normalEenmyCount--;
			startX = 500;
		}
	}
	unsigned long long curTime = GetTickCount64();
	if (startX > 100 && curTime - lastAddNewEnemyTime > 1000) {
		lastAddNewEnemyTime = curTime;
		Add(new EnemyJetNumOne(mBA, startX));
		startX -= 100;
	}
}

void CJETMANAGER::AddMyJet()
{
	bool find = false;
	for (auto temp : jets) {
		if (dynamic_cast<CMyJet*>(temp)) {
			find = true;
		}
	}
	if (!find) {
		Add(new CMyJet(mBA));
	}
}

void CJETMANAGER::AddBoss()
{
	if (normalEenmyCount == 0) {
		Add(new EnemyJetBoss(mBA));
		normalEenmyCount--;
	}
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
	startX = 500;
	normalEenmyCount = 5;
}

bool CJETMANAGER::Run()
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
	AddMyJet();
	AddNormalEnemy();
	AddBoss();
	return stop();
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
