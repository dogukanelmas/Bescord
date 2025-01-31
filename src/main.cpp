#include "../include/LoginScreen.h"

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR lpCmdLine,
	int nCmdShow
) {
	CLoginScreen loginScreen(hInstance);

	if (!loginScreen.Create()) {
		MessageBoxW(nullptr, L"Pencere oluþturulamadý!", L"Hata", MB_ICONERROR);
		return 1;
	}

	loginScreen.Show(nCmdShow);

	MSG msg;
	while (GetMessageW(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return static_cast<int>(msg.wParam);
}
/*
#include <tchar.h>
#include <windows.h>
#include <string>

#include "../include/LoginScreen.h"

const wchar_t className[] = L"LoginWindowClass";

LRESULT __stdcall WndProc(	HWND hWnd,
							UINT msg,
							WPARAM wParam,
							LPARAM lParam
							){
	static std::wstring tempMessage;
	static HWND boxName, boxPassword, hPortEdit, hCapacityEdit, loginButton;

	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);
	int winX = 400;
	int winY = 450;
	HFONT hFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");

	switch (msg) {
	case WM_CREATE:
		CreateWindowEx(0, L"STATIC", L" WELCOME", WS_CHILD | WS_VISIBLE, (winX - 80)/2, (winY - 20)/2 - 120, 80, 20, hWnd, nullptr, nullptr, nullptr);

		CreateWindowEx(0, L"STATIC", L"User Name", WS_CHILD | WS_VISIBLE, (winX - 300) / 2, (winY - 20) / 2 - 70, 80, 20, hWnd, nullptr, nullptr, nullptr);
		boxName = CreateWindowEx(0, L"EDIT", nullptr, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, (winX - 300) / 2 , (winY - 20) / 2 - 40, 300, 20, hWnd, nullptr, nullptr, nullptr);

		CreateWindowEx(0, L"STATIC", L"Password", WS_CHILD | WS_VISIBLE, (winX - 300) / 2, (winY - 20) / 2 - 10, 70, 20, hWnd, nullptr, nullptr, nullptr);
		boxPassword = CreateWindowEx(0, L"EDIT", nullptr, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_PASSWORD, (winX - 300) / 2, (winY - 20) / 2 + 20, 300, 20, hWnd, nullptr, nullptr, nullptr);

		loginButton = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L" LOGIN", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, (winX - 90) / 2, (winY - 20) / 2 + 100, 95, 20, hWnd, (HMENU)1, nullptr, nullptr);

		break;

	case WM_COMMAND:
		wchar_t name[128], ip[128];
		if(wParam == 1){
			GetWindowText(boxName, name, 128);
			MessageBox(NULL, name, L" WELCOME ", ES_CENTER);
			//int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
			// ali kemalin kodu buraya yerleþtireceksin classlara ayýrdýktan sonra
			//DestroyWindow(hWnd); yeni baðlam koyunca bunu yorumdan kaldýrýrsýn
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

int WINAPI _tWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine,
	int nCmdShow
) {
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(wc);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(DKGRAY_BRUSH);//COLOR_WINDOW + 8
	wc.lpszMenuName = NULL;
	wc.lpszClassName = className;
	wc.hIconSm = NULL;

	if (!RegisterClassEx(&wc)) MessageBox(NULL, L"HATA", L"register hatasý", MB_ICONEXCLAMATION | MB_OK);
	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);
	int winX = 400;
	int winY = 450;

	HWND hWnd = CreateWindowEx(
		NULL,
		className,
		(L"escord"),
		WS_POPUP ,
		(screenX - winX) / 2,
		(screenY - winY) / 2,
		winX,
		winY,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg = {};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);//wndProc'a yönlendiriyor
	}
	return msg.wParam;
}
*/