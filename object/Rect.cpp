#include "Rect.h"

CMyRect::CMyRect()
{
	_x = 0;
	_y = 0;
	_w = 0;
	_h = 0;
}

CMyRect::~CMyRect()
{

}

void CMyRect::SetXY(int x, int y)
{
	this->_x = x;
	this->_y = y;
}

void CMyRect::SetWH(int w, int h)
{
	this->_w = w;
	this->_h = h;
}

bool CMyRect::Collision(CMyRect* r)
{
	if (!r)
		return false;

	int L = x;
	int R = x + w - 1;
	int T = y;
	int B = y + h - 1;
	int L2 = r->x;
	int R2 = r->x + r->w - 1;
	int T2 = r->y;
	int B2 = r->y + r->h - 1;

	if (L > R2 || R < L2 || T > B2 || B < T2)
		return false;
	return true;
}
