#include "BulletManager.h"
#include "tool/Output.h"
#include "tool/config.h"

CBUllETMANAGER* CBUllETMANAGER::p = 0;

CBUllETMANAGER::~CBUllETMANAGER()
{
}

void CBUllETMANAGER::Init()
{
	COutput::getInstance()->AddBmp(BMP_BULLET_PATH, BMP_BULLET);
}

void CBUllETMANAGER::Run()
{
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
}

void CBUllETMANAGER::End()
{
	for (auto temp : bullets)
	{
		temp->End();
	}
}

void CBUllETMANAGER::Add(CBASEBULLET* bullet)
{
	bullets.push_back(bullet);
	bullet->Init();
}

CBUllETMANAGER* CBUllETMANAGER::getInstance()
{
	if (!p) {
		p = new CBUllETMANAGER;
	}
	return p;
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
