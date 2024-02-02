#pragma once
#include"Windows.h"
#include"map"
class COutput {
	struct PIC
	{
		HDC hdc;
		int offx;
		int offy;
		int w;
		int h;
		unsigned int c;
	};

	HDC mMainHDC;
	HDC mBackHDC;
	HWND mHwhd;
	int mCw;
	int mCh;
	static COutput* c;
	COutput();
	COutput(const COutput& that);

	std::map<const char*, PIC> mPicMap;
	std::map<const char*, HDC> mHDCmap;
public:
	~COutput();
	static COutput* getInstance();
	void Init(int w, int h, HWND hwnd);
	void Begin();
	void End();

	bool AddBmp(LPCWSTR srcPath, const char* key);
	bool AddPic(const char* bmpKey, const char* picKey, int offx, int offy, int w, int h, unsigned int c);
	void Draw(const char*key,int x,int y,float sx = 1.0f,float sy =1.0f);

};