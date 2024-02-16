#pragma once
#include "vector"

class CPOS
{
public:
	CPOS(int x,int y);
	CPOS(const CPOS& that);
	~CPOS();
	int getX();
	int getY();
private:
	int x;
	int y;
};

class CMOVEPATH
{
public:
	CMOVEPATH();
	~CMOVEPATH();
	CMOVEPATH* add(CPOS pos);
	bool calculatePos(float* xp, float* yp);
	bool finish();
private:
	std::vector<CPOS> posList;
	int index;
	bool xFinish;
	bool yFinish;
};