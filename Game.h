#pragma once
#include "Windows.h"
#include "tool/config.h"
#include "vector"

class CSCENE;

class Game {
private:
	Game();
	Game(const Game& that);
	static Game* gamep;
	std::vector<CSCENE*> mList;
	int index;
public:
	static Game* getInstance();
	void Init(HWND hWnd);
	void Run();
	void End();
};
