#include "path.h"

CMOVEPATH::CMOVEPATH()
{
	index = 0;
	xFinish = false;
	yFinish = false;
}

CMOVEPATH::~CMOVEPATH()
{
}

CMOVEPATH* CMOVEPATH::add(CPOS pos)
{
	posList.push_back(pos);
	return this;
}

bool CMOVEPATH::calculatePos(float* xp, float* yp)
{
	bool up = false;
	float offset = 0.3f;

	if (index + 1 <= posList.size() - 1) {
		CPOS temp = posList[index];
		CPOS tempNext = posList[index+1];
		int offsetX = tempNext.getX() - temp.getX();
		if (offsetX < 0) {
			offsetX = 0 - offsetX;
		}
		int offsetY = tempNext.getY() - temp.getY();
		if (offsetY < 0) {
			offsetY = 0 - offsetY;
		}
		float ratio = 0.0f;
		if (offsetX == 0) {
			ratio = 1.0f;
			xFinish = true;
		}
		else {
			ratio = offsetY / offsetX;
		}
		if(offsetY==0){
			yFinish = true;
		}
		if (!xFinish) {
			if ((*xp) > tempNext.getX()) {
				(*xp) -= offset;
				if ((*xp) <= tempNext.getX()) {
					xFinish = true;
				}
			}
			else if ((*xp) < tempNext.getX()) {
				(*xp) += offset;
				if ((*xp) >= tempNext.getX()) {
					xFinish = true;
				}
			}
		}
		if (!yFinish) {
			if ((*yp) > tempNext.getY()) {
				(*yp) -= (offset * ratio);
				up = true;
				if ((*yp) <= tempNext.getY()) {
					yFinish = true;
				}
			}
			else if ((*yp) < tempNext.getY()) {
				(*yp) += (offset * ratio);
				up = false;
				if ((*yp) >= tempNext.getY()) {
					yFinish = true;
				}
			}
		}

		if (xFinish&&yFinish) {
			index++;
			xFinish = false;
			yFinish = false;
		}
	}
	return up;
}

bool CMOVEPATH::finish()
{
	return index>=posList.size()-1;
}

CPOS::CPOS(int x, int y)
{
	this->x = x;
	this->y = y;
}

CPOS::CPOS(const CPOS& that)
{
	this->x = that.x;
	this->y = that.y;
}

CPOS::~CPOS()
{
}

int CPOS::getX()
{
	return x;
}

int CPOS::getY()
{
	return y;
}
