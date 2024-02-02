#pragma once

class CRect
{
private:
	int _x;
	int _y;
	int _w;
	int _h;
public:
	CRect();
	~CRect();
	const int& x = _x;
	const int& y = _y;
	const int& w = _w;
	const int& h = _h;
	void SetXY(int x, int y);
	void SetWH(int w, int h);
	bool Collision(CRect* r);
};
