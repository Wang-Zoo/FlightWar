#include "UI.h"
#include "tool/Output.h"
#include "tool/config.h"
CBASEUI::CBASEUI()
{
}

CBASEUI::~CBASEUI()
{
}

BACKGROUND::BACKGROUND()
{
}

BACKGROUND::~BACKGROUND()
{
}

void BACKGROUND::Init()
{
	COutput::getInstance()->AddPic(BMP_BG, KEY_BG, 0, 0, _CLIENT_W, _CLIENT_H, RGB(255, 0, 0));
}

void BACKGROUND::Run()
{
	COutput::getInstance()->Draw(KEY_BG, 0, (int)moveY);
	COutput::getInstance()->Draw(KEY_BG, 0, (int)moveY- _CLIENT_H);
	moveY+=0.5f;
	if (moveY >= _CLIENT_H) {
		moveY = 0.0f;
	}
}

void BACKGROUND::End()
{
}
