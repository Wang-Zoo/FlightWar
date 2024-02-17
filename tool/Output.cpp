#include "Output.h"

COutput* COutput::c = 0;

COutput::COutput()
{
	mMainHDC = 0;
	mBackHDC = 0;
	mCw = 0;
	mCh = 0;
	mHwhd = 0;
}

COutput::COutput(const COutput& that)
{

}

COutput::~COutput()
{
}

COutput* COutput::getInstance()
{
	if (!c) {
		c = new COutput;
	}
	return c;
}

void COutput::Init(int w,int h,HWND hwnd)
{
	if (!hwnd) {
		return;
	}
	mCh = h;
	mCw = w;
	mHwhd = hwnd;
	mMainHDC = GetDC(hwnd);
	if (!mMainHDC) {
		return;
	}
	mBackHDC = CreateCompatibleDC(mMainHDC);
	HBITMAP hbmp = CreateCompatibleBitmap(mMainHDC, mCw, mCh);
	DeleteObject(SelectObject(mBackHDC, hbmp));
	DeleteObject(hbmp);
}

void COutput::Begin()
{
	BitBlt(mBackHDC, 0, 0, mCw, mCh, 0, 0, 0, WHITENESS);
}

void COutput::fillBlack()
{
	BitBlt(mBackHDC, 0, 0, mCw, mCh, 0, 0, 0, BLACKNESS);
}

void COutput::End()
{
	BitBlt(mMainHDC, 0, 0, mCw, mCh, mBackHDC, 0, 0, SRCCOPY);
}

bool COutput::AddBmp(LPCWSTR srcPath, const char* key)
{
	if (!srcPath || !key) {
		return false;
	}
	auto it = mHDCmap.find(key);
	if (it != mHDCmap.end()) {
		return false;
	}
	HBITMAP hbmp = (HBITMAP)LoadImage(0,srcPath,IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
	if (!hbmp) {
		return false;
	}
	HDC bmpDC = CreateCompatibleDC(mMainHDC);
	DeleteObject(SelectObject(bmpDC, hbmp));
	DeleteObject(hbmp);
	mHDCmap.insert(std::pair<const char*, HDC>(key, bmpDC));
	return true;
}

bool COutput::AddPic(const char* bmpKey, const char* picKey, int offx, int offy, int w, int h, unsigned int c)
{
	if (!bmpKey || !picKey) {
		return false;
	}
	//判断pickey是否已经被用了
	auto picIT = mPicMap.find(picKey);
	if (picIT != mPicMap.end()) {
		return false;
	}
	//通过bmpkey找出HDC
	auto bmpIT = mHDCmap.find(bmpKey);
	if (bmpIT == mHDCmap.end()) {
		return false;
	}
	PIC pic;
	pic.offx = offx;
	pic.offy = offy;
	pic.w = w;
	pic.h = h;
	pic.c = c;
	pic.hdc = (*bmpIT).second;

	mPicMap.insert(std::pair<const char *,PIC>(picKey,pic));
	return true;
}

void COutput::Draw(const char* key, int x, int y, float sx, float sy)
{
	if (!key) {
		return;
	}
	auto it = mPicMap.find(key);
	if (it == mPicMap.end()) {
		return;
	}

	PIC* pic = &it->second;
	TransparentBlt(mBackHDC, x, y, pic->w * sx, pic->h * sy, pic->hdc, pic->offx, pic->offy, pic->w, pic->h, pic->c);
}

void COutput::Draw(const char* key, int x, int y, int targetW, int targetH)
{
	if (!key) {
		return;
	}
	auto it = mPicMap.find(key);
	if (it == mPicMap.end()) {
		return;
	}

	PIC* pic = &it->second;
	TransparentBlt(mBackHDC, x, y, targetW, targetH, pic->hdc, pic->offx, pic->offy, targetW, targetH, pic->c);
}

void COutput::DrawCustomText(LPCWSTR data, int x, int y,int length)
{
	SetBkColor(mBackHDC, RGB(0,0,0));
	SetTextColor(mBackHDC, RGB(255, 255, 255));
	TextOut(mBackHDC, x, y, data, length);
}
