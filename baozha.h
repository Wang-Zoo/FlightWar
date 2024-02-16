#pragma once

class CBAOZHA
{
public:
	CBAOZHA();
	~CBAOZHA();
	void show(int x,int y,int w, int h);
	bool finish();
private:
	int index;
	unsigned long long lastTime;
};
