#include "scene.h"
#include "Windows.h"
#include "manager/UIManager.h"
#include "manager/JetManager.h"
#include "manager/BulletManager.h"
#include "tool/Output.h"
#include "tool/config.h"
CSCENE::CSCENE()
{
}

CSCENE::~CSCENE()
{
}


CStartScene::CStartScene() :CSCENE()
{

}

void CStartScene::Init()
{
	COutput::getInstance()->AddBmp(BMP_STARTUI_PATH, BMP_START);
	COutput::getInstance()->AddPic(BMP_START, KEY_BLACK_START, 19, 5, START_WIDTH, START_HEIGHT, RGB(13, 237, 13));
	COutput::getInstance()->AddPic(BMP_START, KEY_COLOR_START, 23, 254, START_WIDTH, START_HEIGHT, RGB(13, 237, 13));
	startY = 0 - START_HEIGHT;
	chooseY = 350;
}

int CStartScene::Run()
{
	auto curTime = GetTickCount64();
	if (curTime - lastTime > 10) {
		lastTime = curTime;
		startY++;
		if (startY > (50)) {
			startY = 50;
		}
	}

	COutput::getInstance()->fillBlack();
	COutput::getInstance()->Draw(startY < 50 ? KEY_BLACK_START : KEY_COLOR_START, (_CLIENT_W - START_WIDTH) / 2, startY);
	if (startY == 50) {
		COutput::getInstance()->DrawCustomText(L"GAME START", 350, 350, 10);
		COutput::getInstance()->DrawCustomText(L"EXIT", 350, 390, 4);
		COutput::getInstance()->DrawCustomText(L"->", 330, chooseY, 2);
		if (GetAsyncKeyState('W') & 0x8000) {
			chooseY = 350;
		}
		else if (GetAsyncKeyState('S') & 0x8000) {
			chooseY = 390;
		}
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			if (chooseY == 350) {
				return SCENE_NEXT;
			}
			else if (chooseY == 390) {
				return SCENE_EXIT;
			}
			else {
				return SCENE_IDOL;
			}
		}
		else {
			return SCENE_IDOL;
		}
	}else {
		return SCENE_IDOL;
	}
}

void CStartScene::End()
{
}

CNumOneScene::CNumOneScene():CSCENE()
{
}

void CNumOneScene::Init()
{
	CUIMANAGER* up = CUIMANAGER::getInstance();
	CBUllETMANAGER* bp = CBUllETMANAGER::getInstance();
	CJETMANAGER* jp = CJETMANAGER::getInstance();

	bp->End();

	bp->setJetAction(jp);
	jp->setBA(bp);

	mList.push_back(up);
	mList.push_back(bp);
	mList.push_back(jp);

	for (auto temp : mList) {
		temp->Init();
	}
}

int CNumOneScene::Run()
{
	for (auto temp : mList) {
		if (temp->Run())
			return SCENE_NEXT;
	}
	return SCENE_IDOL;
}

void CNumOneScene::End()
{
	for (auto temp : mList) {
		temp->End();
		delete temp;
	}
}

CEndScene::CEndScene()
{
}

void CEndScene::Init()
{
	chooseY = 350;
}

int CEndScene::Run()
{
	COutput::getInstance()->fillBlack();
	COutput::getInstance()->DrawCustomText(L"GAME OVER", 340, 200, 9);
	COutput::getInstance()->DrawCustomText(L"RESTART", 350, 350, 7);
	COutput::getInstance()->DrawCustomText(L"EXIT", 350, 390, 4);
	COutput::getInstance()->DrawCustomText(L"->", 330, chooseY, 2);

	if (GetAsyncKeyState('W') & 0x8000) {
		chooseY = 350;
	}
	else if (GetAsyncKeyState('S') & 0x8000) {
		chooseY = 390;
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
		if (chooseY == 350) {
			return SCENE_PRE;
		}
		else if (chooseY == 390) {
			return SCENE_EXIT;
		}
		else {
			return SCENE_IDOL;
		}
	}
	else {
		return SCENE_IDOL;
	}

}

void CEndScene::End()
{
}
