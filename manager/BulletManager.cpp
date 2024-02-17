#include "BulletManager.h"
#include "tool/Output.h"
#include "tool/config.h"
#include "JetManager.h"
CBUllETMANAGER* CBUllETMANAGER::p = 0;

CBUllETMANAGER::~CBUllETMANAGER()
{
}

void CBUllETMANAGER::Init()
{
	COutput::getInstance()->AddBmp(BMP_BULLET_PATH, BMP_BULLET);
	COutput::getInstance()->AddBmp(BMP_FIRE_BULLET_PATH, BMP_FIRE_BULLET);
	COutput::getInstance()->AddBmp(BMP_ENEMY_BULLET_PATH, BMP_ENEMY_BULLET);
	//Ô¤Éè»ðÑæ×Óµ¯
	Add(new MyJetBulletNumTwo);
}

bool CBUllETMANAGER::Run()
{
	for (auto temp:bullets)
	{
		if (temp->isDead()) {
			continue;
		}
		bool isAllen = dynamic_cast<MyJetBulletNumTwo*>(temp) || dynamic_cast<MyJetBulletNumOne*>(temp);
		bool collision = mJP->collision(temp->getRectP(),!isAllen);
		if (collision&& !dynamic_cast<MyJetBulletNumTwo*>(temp)) {
			temp->dead();
		}
	}
	auto it = bullets.begin();
	for (;it!=bullets.end();)
	{
		if ((*it)->isDead()) {
			delete(*it);
			it = bullets.erase(it);
		}
		else {
			(*it)->Run();
			it++;
		}
	}
	return false;
}

void CBUllETMANAGER::End()
{
	for (auto temp : bullets)
	{
		temp->End();
	}
	auto it = bullets.begin();
	for (;it!=bullets.end();)
	{
		(*it)->End();
		delete *it;
		it = bullets.erase(it);
	}
}

void CBUllETMANAGER::Add(CBASEBULLET* bullet)
{
	bullets.push_back(bullet);
	bullet->Init();
}

void CBUllETMANAGER::fireBullet(int x, int y,bool fire)
{
	if (bullets.size()>0&& bullets[0] && dynamic_cast<MyJetBulletNumTwo*>(bullets[0])) {
		MyJetBulletNumTwo* temp = dynamic_cast<MyJetBulletNumTwo*>(bullets[0]);
		if (fire) {
			temp->fire(x, y);
		}
		else {
			temp->setXY(x, y);
		}
	}
}

CBUllETMANAGER* CBUllETMANAGER::getInstance()
{
	if (!p) {
		p = new CBUllETMANAGER();
	}
	return p;
}

void CBUllETMANAGER::setJetAction(CJetAction* jp)
{
	this->mJP = jp;
}

CBUllETMANAGER::CBUllETMANAGER()
{
}

CBUllETMANAGER::CBUllETMANAGER(const CBUllETMANAGER& that)
{
}

CBulletAction::CBulletAction()
{
}

CBulletAction::~CBulletAction()
{
}
