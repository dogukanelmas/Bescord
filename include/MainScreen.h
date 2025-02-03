#pragma once
#include <windows.h>
#include <string>
#include <vector>

class CMainScreen {
public:
    CMainScreen(HINSTANCE hInstance);
    ~CMainScreen();

    bool Create();
    void Show(int nCmdShow);
    HWND GetHandle() const { return m_hWnd; }

private:
    LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void AdjustComponents(HWND hWnd);

    HWND m_hWnd;
    HINSTANCE m_hInstance;
    std::wstring m_className = L"MainWindowClass";

    // Bileþenler
    HWND hCloseButton, hFullscreenButton, hMinimizeButton;
    HWND hChatArea, hServerList, hAddServerButton, hCreateServerButton;
    HWND hMessageInput, hSendButton;

    std::vector<std::wstring> serverList; // Sunucu listesi
};