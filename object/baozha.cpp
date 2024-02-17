#include "baozha.h"
#include "tool/Output.h"
#include "tool/config.h"

CBAOZHA::CBAOZHA()
{
	COutput::getInstance()->AddPic(BMP_JET, KEY_BAOZHA_ONE, 0, 156, BZ_WIDTH, BZ_HEIGHT, RGB(13, 237, 13));
	COutput::getInstance()->AddPic(BMP_JET, KEY_BAOZHA_TWO, 76, 156, BZ_WIDTH, BZ_HEIGHT, RGB(13, 237, 13));
	COutput::getInstance()->AddPic(BMP_JET, KEY_BAOZHA_THERE, 132, 156, BZ_WIDTH, BZ_HEIGHT, RGB(13, 237, 13));
	index = 0;
}

CBAOZHA::~CBAOZHA()
{

}

void CBAOZHA::show(int x,int y,int w,int h)
{

	x = x + (w - BZ_WIDTH) / 2;
	y = y + (h - BZ_HEIGHT) / 2;

	unsigned long long curTime = GetTickCount64();
	if (curTime - lastTime > 70) {
		lastTime = curTime;
		index++;
	}
	if (index == 1) {
		COutput::getInstance()->Draw(KEY_BAOZHA_ONE, x, y);
	}
	else if (index == 2) {
		COutput::getInstance()->Draw(KEY_BAOZHA_TWO, x, y);
	}
	else if (index == 3) {
		COutput::getInstance()->Draw(KEY_BAOZHA_THERE, x, y);
	}
}

bool CBAOZHA::finish()
{
	return index > 3;
}
