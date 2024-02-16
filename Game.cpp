#include "Game.h"
#include "manager/UIManager.h"
#include "manager/JetManager.h"
#include "manager/BulletManager.h"
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
	CUIMANAGER* up = CUIMANAGER::getInstance();
	CBUllETMANAGER* bp = CBUllETMANAGER::getInstance();
	CJETMANAGER* jp = CJETMANAGER::getInstance();

	bp->setJetAction(jp);
	jp->setBA(bp);

	mList.push_back(up);
	mList.push_back(bp);
	mList.push_back(jp);

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
