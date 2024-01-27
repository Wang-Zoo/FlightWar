// FlightWar.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "FlightWar.h"
#pragma comment(lib, "msimg32.lib")

#define MAX_LOADSTRING 100
#define _CLIENT_W 763
#define _CLIENT_H 706


int g_JetWidth = 36;
int g_JetHeight = 46;
int g_JetStartX = (_CLIENT_W - g_JetWidth)/2;
int g_JetStartY = (_CLIENT_H - g_JetHeight-100);
int g_dirState = 0;
int g_actionTime = 0;


HBITMAP hbmp[2];
HWND hWnd;
// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	hbmp[0] = (HBITMAP)LoadImage(0, L"pic\\bg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hbmp[1] = (HBITMAP)LoadImage(0, L"pic\\jet_action.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此处放置代码。

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_FLIGHTWAR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FLIGHTWAR));

	MSG msg;

	// 主消息循环:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	KillTimer(hWnd, 0);
	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FLIGHTWAR));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FLIGHTWAR);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中


	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);
	RECT rect
		=
	{
		(sw - _CLIENT_W) / 2,
		(sh - _CLIENT_H) / 2,
		_CLIENT_W + (sw - _CLIENT_W) / 2,
		_CLIENT_H + (sh - _CLIENT_H) / 2
	};

	AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);


	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);

	// 移除菜单栏
	HMENU hMenu = GetMenu(hWnd);
	SetMenu(hWnd, NULL);
	DestroyMenu(hMenu);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//设置定时器
	SetTimer(hWnd, 112, 32, 0);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;

		//清空画布
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT rect;
		GetClientRect(hWnd, &rect); // 获取画布的矩形区域
		HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0)); // 创建背景色画刷
		FillRect(hdc, &rect, hBrush); // 填充画布为背景色
		DeleteObject(hBrush); // 删除画刷



		HDC bmpdc[2];

		//创建显示设备（兼容设备）
		bmpdc[0] = CreateCompatibleDC(hdc);
		bmpdc[1] = CreateCompatibleDC(hdc);
		HBITMAP oldbmp1 = (HBITMAP)SelectObject(bmpdc[0], hbmp[0]);
		HBITMAP oldbmp2 = (HBITMAP)SelectObject(bmpdc[1], hbmp[1]);

		static int bg1Y = 0;
		static int bg2Y = 0;
		bg1Y += 10;
		bg2Y += 10;

		if (bg1Y > _CLIENT_H)
			bg1Y = 0;
		if (bg2Y > _CLIENT_H)
			bg2Y = 0;

		BitBlt(hdc, 0, bg1Y, _CLIENT_W, _CLIENT_H - bg1Y, bmpdc[0], 0, 0, SRCCOPY);
		BitBlt(hdc, 0, 0, _CLIENT_W, bg2Y, bmpdc[0], 0, _CLIENT_H - bg2Y, SRCCOPY);


		if (GetAsyncKeyState('W') & 0x01) {
			g_JetStartY -= 30;
			if (g_JetStartY < 0) {
				g_JetStartY = 0;
			}
		}
		else if (GetAsyncKeyState('S') & 0x01) {
			g_JetStartY += 30;
			if (g_JetStartY > _CLIENT_H - g_JetHeight) {
				g_JetStartY = _CLIENT_H - g_JetHeight;
			}
		}
		if (GetAsyncKeyState('A') & 0x01) {
			g_JetStartX -= 30;
			if (g_JetStartX < 0) {
				g_JetStartX = 0;
			}
			g_actionTime = 0;
			g_dirState = 1;
		}
		else if (GetAsyncKeyState('D') & 0x01) {
			g_JetStartX += 30;
			if (g_JetStartX > _CLIENT_W - g_JetWidth) {
				g_JetStartX = _CLIENT_W - g_JetWidth;
			}
			g_actionTime = 0;
			g_dirState = 2;
		}
		else {
			g_dirState = 0;
		}


		switch (g_dirState)
		{
		case 0:
			TransparentBlt(hdc, g_JetStartX, g_JetStartY, 45 - 1, 54 - 0, bmpdc[1], 1, 0, 45 - 1, 54 - 0, RGB(13, 237, 13));
			break;
		case 1:
			TransparentBlt(hdc, g_JetStartX, g_JetStartY, 81 - 45, 54 - 0, bmpdc[1], 45, 0, 81 - 45, 54 - 0, RGB(13, 237, 13));
			break;
		case 2:
			TransparentBlt(hdc, g_JetStartX, g_JetStartY, 117 - 81, 54 - 0, bmpdc[1], 81, 0, 117 - 81, 54 - 0, RGB(13, 237, 13));
			break;
		default:
			break;
		}

		//if (g_dirState) {
		//	g_actionTime++;
		//	if (g_actionTime > 5) {
		//		g_actionTime = 0;
		//		g_dirState = 0;
		//	}
		//}


		//TransparentBlt(hdc, 0,0,_CLIENT_W, _CLIENT_H,bmpdc[0], 0,0,_CLIENT_W,_CLIENT_H, RGB(255, 255, 255));


		//wchar_t buffer[50]; // 存储转换后的宽字符字符串
		//swprintf_s(buffer, 50, L"%d", g_JetStartY); // 将整数转换为宽字符字符串
		//LPCWSTR result = buffer; // 将宽字符字符串转换为 LPCWSTR 类型
		//TextOut(hdc, 40, 100, result, wcslen(result));  

		//int jetLeftWidth = 78 - 41;
		//int jetLeftHeight = 50 - 7;
		//TransparentBlt(hdc, 100, 200, jetLeftWidth, jetLeftHeight, bmpdc[0], 41, 7, jetLeftWidth, jetLeftHeight, RGB(13, 247, 13));

		//int jetRightWidth = 116 - 86;
		//int jetRightHeight = 52 - 9;
		//TransparentBlt(hdc, 100, 300, jetRightWidth, jetRightHeight, bmpdc[0], 86, 9, jetRightWidth, jetRightHeight, RGB(13, 247, 13));

		 //将老版位图选入并且删除
		SelectObject(bmpdc[0], oldbmp1);
		DeleteObject(bmpdc[0]);
		SelectObject(bmpdc[1], oldbmp2);
		DeleteObject(bmpdc[1]);

		UpdateWindow(hWnd); // 刷新画布
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		if (wParam == 112) {
			// 定时器消息
			// 执行绘制操作
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
