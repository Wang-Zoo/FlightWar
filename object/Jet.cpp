#include "Jet.h"
#include "tool/Output.h"
#include "tool/config.h"

CJet::CJet()
{
}

CJet::~CJet()
{
}

CMyJet::CMyJet()
{
}

CMyJet::~CMyJet()
{
}

void CMyJet::Init()
{
	COutput::getInstance()->AddPic(BMP_JET, KEY_MY_JET_IDOL, 1, 0, 44, 54, RGB(13, 237, 13));
	COutput::getInstance()->AddPic(BMP_JET, KEY_MY_JET_LEFT, 45, 0, 36, 54, RGB(13, 237, 13));
	COutput::getInstance()->AddPic(BMP_JET, KEY_MY_JET_RIGHT, 81, 0, 36, 54, RGB(13, 237, 13));

}

void CMyJet::Run()
{
	COutput::getInstance()->Draw(KEY_MY_JET_RIGHT, 100, 100);
}

void CMyJet::End()
{
}
