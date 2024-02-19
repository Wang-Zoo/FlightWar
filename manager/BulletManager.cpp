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
	COutput::getInstance()->AddBmp(BMP_ALL_BULLET_PATH, BMP_BULLET);
	//预设火焰子弹
	Add(new MyJetBulletNumTwo);
}

bool CBUllETMANAGER::Run()
{
	//子弹与飞机的碰撞
	for (auto temp:bullets)
	{
		if (temp->isDead()) {
			continue;
		}
		bool isAllen = dynamic_cast<MyJetBulletNumTwo*>(temp) || dynamic_cast<MyJetBulletNumOne*>(temp);
		bool collision = mJP->collision(temp->getRectP(),!isAllen, dynamic_cast<MyJetBulletNumTwo*>(temp)?0.01f:1.0f);
		if (collision&& !dynamic_cast<MyJetBulletNumTwo*>(temp)) {
			temp->dead();
		}
	}
	//子弹与子弹的碰撞
	for (size_t i = 0; i < bullets.size(); i++)
	{
		CBASEBULLET* temp = bullets[i];
		if (temp->isDead()) {
			continue;
		}
		for (size_t j = i+1; j < bullets.size(); j++)
		{
			CBASEBULLET* target = bullets[j];
			if (target->isDead()) {
				continue;
			}
			bool collision = temp->getRectP()->Collision(target->getRectP());
			if (collision) {
				temp->dead();
				target->dead();
				break;
			}
		}
	}
	auto it = bullets.begin();
	for (;it!=bullets.end();)
	{
		if ((*it)->canDestory()) {
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
