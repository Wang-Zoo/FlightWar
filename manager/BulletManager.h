#pragma once
#include"vector"
#include"object/Bullet.h"
#include "BaseManager.h"

class CJetAction;

class CBulletAction
{
public:
	CBulletAction();
	~CBulletAction();
	virtual void Add(CBASEBULLET*) = 0;
	virtual void fireBullet(int x, int y,bool fire) = 0;
};

//·É»ú¹ÜÀíÆ÷
class CBUllETMANAGER :public CBASEMANAGER,public CBulletAction
{
public:
	~CBUllETMANAGER();
	void Init();
	bool Run();
	void End();
	void Add(CBASEBULLET*);
	void fireBullet(int x, int y,bool fire);
	static CBUllETMANAGER* getInstance();
	void setJetAction(CJetAction* jp);
private:
	CJetAction* mJP;
	static CBUllETMANAGER* p;
	CBUllETMANAGER();
	CBUllETMANAGER(const CBUllETMANAGER& that);
	std::vector<CBASEBULLET*> bullets;
};

