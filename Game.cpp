#include "Game.h"
#include "tool/Output.h"
#include "tool/config.h"
#include "scene/scene.h"

Game* Game::gamep = 0;

Game::Game()
{
}

Game::Game(const Game& that)
{
}

Game* Game::getInstance()
{
	if (!gamep) {
		gamep = new Game;
	}
	return gamep;
}

void Game::Init(HWND hWnd)
{
	index = 0;
	COutput::getInstance()->Init(_CLIENT_W, _CLIENT_H, hWnd);
	mList.push_back(new CStartScene);
	mList.push_back(new CNumOneScene);
	mList.push_back(new CEndScene);
	for (auto temp:mList )
	{
		temp->Init();
	}
}

void Game::Run()
{
	COutput::getInstance()->Begin();
	int state = mList[index]->Run();
	COutput::getInstance()->End();
	if (state == SCENE_NEXT) {
		index++;
		if (index >= mList.size() - 1) {
			index = mList.size() - 1;
		}
	}
	else if (state == SCENE_PRE) {
		index--;
		if (index <= 0) {
			index = 0;
		}
		mList[index]->Init();
	}
	else if (state == SCENE_EXIT) {
		PostQuitMessage(0);
	}
}

void Game::End()
{
	for (auto temp : mList)
	{
		temp->End();
		delete temp;
	}
}
