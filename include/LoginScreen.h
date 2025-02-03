#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include "MainScreen.h"

class CLoginScreen {
public:
    CLoginScreen(HINSTANCE hInstance);
    ~CLoginScreen();

    bool Create();
    void Show(int nCmdShow);

private:
    LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    void CreateLoginUI(HWND hWnd);
    void CreateRegisterUI(HWND hWnd);

    int winX = 400;
    int winY = 450;

    HWND m_hWnd;
    HWND boxName;
    HWND loginButton;
    HWND boxPassword;
    HWND boxForgat;
    HWND click;
    HINSTANCE m_hInstance;
    std::wstring m_className = L"LoginWindowClass";
    bool screen = true;
};