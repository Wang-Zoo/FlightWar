#pragma once
#include "Windows.h"
#include "tool/config.h"
#include "manager/BaseManager.h"
#include "vector"

class Game {
private:
	Game();
	Game(const Game& that);
	static Game* gamep;
	std::vector<CBASEMANAGER*> mList;
public:
	static Game* getInstance();
	void Init(HWND hWnd);
	void Run();
	void End();
};
