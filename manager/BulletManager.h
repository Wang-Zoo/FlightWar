#pragma once
#include"vector"
#include"object/Bullet.h"
#include "BaseManager.h"
class CBulletAction
{
public:
	CBulletAction();
	~CBulletAction();
	virtual void Add(CBASEBULLET*) = 0;
	virtual void fireBullet(int x, int y) = 0;
};

//·É»ú¹ÜÀíÆ÷
class CBUllETMANAGER :public CBASEMANAGER,public CBulletAction
{
public:
	~CBUllETMANAGER();
	void Init();
	void Run();
	void End();
	void Add(CBASEBULLET*);
	void fireBullet(int x, int y);
	static CBUllETMANAGER* getInstance();
private:
	static CBUllETMANAGER* p;
	CBUllETMANAGER();
	CBUllETMANAGER(const CBUllETMANAGER& that);
	std::vector<CBASEBULLET*> bullets;
};

