#pragma once

#include <windows.h>
#include <string>
//#include "resource.h"

class CLoginScreen {
public:
	CLoginScreen(HINSTANCE hInstance);
	~CLoginScreen();

	bool Create();
	void Show(int nCmdShow);

private:
	LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	int winX = 400;
	int winY = 450;

	HWND m_hWnd;
	HWND boxName;
	HWND loginButton;
	HWND boxPassword;
	HINSTANCE m_hInstance;
	std::wstring m_className = L"LoginWindowClass";
};