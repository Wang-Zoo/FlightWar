#include "Game.h"
#include "manager/UIManager.h"
#include "manager/JetManager.h"
#include "tool/Output.h"
#include "tool/config.h"

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
	COutput::getInstance()->Init(_CLIENT_W, _CLIENT_H, hWnd);
	mList.push_back(CUIMANAGER::getInstance());
	mList.push_back(CJETMANAGER::getInstance());

	for (auto temp : mList) {
		temp->Init();
	}
}

void Game::Run()
{
	COutput::getInstance()->Begin();

	for (auto temp : mList) {
		temp->Run();
	}

	COutput::getInstance()->End();
}

void Game::End()
{
	for (auto temp : mList) {
		temp->End();
		delete temp;
	}
}
