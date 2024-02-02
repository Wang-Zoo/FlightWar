#include "Game.h"
#include "manager/UIManager.h"
#include "tool/Output.h"
#include "tool/config.h"

void GameInit(HWND hWnd)
{
	COutput::getInstance()->Init(_CLIENT_W, _CLIENT_H, hWnd);

	CUIMANAGER::getInstance()->Init();
}

void GameRun()
{
	COutput::getInstance()->Begin();

	CUIMANAGER::getInstance()->Run();

	COutput::getInstance()->End();
}

void GameEnd()
{
	CUIMANAGER::getInstance()->End();
}
