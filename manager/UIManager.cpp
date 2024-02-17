#include "UIManager.h"
#include "tool/Output.h"
#include "tool/config.h"

CUIMANAGER* CUIMANAGER::manager = 0;

CUIMANAGER::CUIMANAGER()
{

}

CUIMANAGER::~CUIMANAGER()
{

}

void CUIMANAGER::Init()
{
	COutput::getInstance()->AddBmp(BMP_BG_PATH, BMP_BG);
	uiList.push_back(new BACKGROUND);

	for ( auto temp:uiList)
	{
		temp->Init();
	}
}

bool CUIMANAGER::Run()
{
	for (auto temp : uiList)
	{
		temp->Run();
	}
	return false;
}

void CUIMANAGER::End()
{
	for (auto temp : uiList)
	{
		temp->End();
		delete temp;
	}
}

CUIMANAGER* CUIMANAGER::getInstance()
{
	if (!manager) {
		manager = new CUIMANAGER;
	}
	return manager;
}
