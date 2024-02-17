#pragma once

class CBZ
{
public:
	CBZ();
	~CBZ();
	void show(int x,int y,int w, int h);
	bool finish();
private:
	int index;
	unsigned long long lastTime;
};
