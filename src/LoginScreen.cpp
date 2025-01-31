#include "../include/LoginScreen.h"
#include <windowsx.h>

CLoginScreen::CLoginScreen(HINSTANCE hInstance) : m_hInstance(hInstance), m_hWnd(nullptr) {}

CLoginScreen::~CLoginScreen() {
    if (m_hWnd) DestroyWindow(m_hWnd);
}

bool CLoginScreen::Create() {
    WNDCLASSEXW wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = CLoginScreen::WndProc;
    wc.hInstance = m_hInstance;
    //wc.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCEW(IDI_ICON1));
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(DKGRAY_BRUSH);
    wc.lpszClassName = m_className.c_str();

    if (!RegisterClassExW(&wc)) {
        MessageBoxW(nullptr, L"Pencere sýnýfý kaydedilemedi!", L"Hata", MB_ICONERROR);
        return false;
    }

    m_hWnd = CreateWindowExW(
        0,
        m_className.c_str(),
        L"ESCORD",
        WS_POPUP,
        (GetSystemMetrics(SM_CXSCREEN) - winX) / 2,
        (GetSystemMetrics(SM_CYSCREEN) - winY) / 2,
        400, 450,
        nullptr,
        nullptr,
        m_hInstance,
        this
    );

    return m_hWnd != nullptr;
}

void CLoginScreen::Show(int nCmdShow) {
    ShowWindow(m_hWnd, nCmdShow);
    UpdateWindow(m_hWnd);
}

LRESULT CLoginScreen::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowEx(0, L"STATIC", L" WELCOME", WS_CHILD | WS_VISIBLE, (winX - 80) / 2, (winY - 20) / 2 - 120, 80, 20, hWnd, nullptr, nullptr, nullptr);

        CreateWindowEx(0, L"STATIC", L"User Name", WS_CHILD | WS_VISIBLE, (winX - 300) / 2, (winY - 20) / 2 - 70, 80, 20, hWnd, nullptr, nullptr, nullptr);
        boxName = CreateWindowEx(0, L"EDIT", nullptr, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER, (winX - 300) / 2, (winY - 20) / 2 - 40, 300, 20, hWnd, nullptr, nullptr, nullptr);

        CreateWindowEx(0, L"STATIC", L"Password", WS_CHILD | WS_VISIBLE, (winX - 300) / 2, (winY - 20) / 2 - 10, 70, 20, hWnd, nullptr, nullptr, nullptr);
        boxPassword = CreateWindowEx(0, L"EDIT", nullptr, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_PASSWORD, (winX - 300) / 2, (winY - 20) / 2 + 20, 300, 20, hWnd, nullptr, nullptr, nullptr);

        loginButton = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L" LOGIN", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, (winX - 90) / 2, (winY - 20) / 2 + 100, 95, 20, hWnd, (HMENU)1, nullptr, nullptr);

        break;

    case WM_COMMAND:
        wchar_t name[128], ip[128];
        if (wParam == 1) {
            GetWindowText(boxName, name, 128);
            MessageBox(NULL, name, L" WELCOME ", ES_CENTER);
            //int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
            // ali kemalin kodu buraya yerleþtireceksin classlara ayýrdýktan sonra
            //DestroyWindow(hWnd); yeni baðlam koyunca bunu yorumdan kaldýrýrsýn
        }

        break;
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
            PostQuitMessage(0);
        break;
    case WM_DESTROY:
        //int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
                // ali kemalin kodu buraya yerleþtireceksin classlara ayýrdýktan sonra
                //DestroyWindow(hWnd); yeni baðlam koyunca bunu yorumdan kaldýrýrsýn
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK CLoginScreen::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    CLoginScreen* pThis = nullptr;

    if (msg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = reinterpret_cast<CLoginScreen*>(pCreate->lpCreateParams);
        SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
        pThis->m_hWnd = hWnd;
    }
    else {
        pThis = reinterpret_cast<CLoginScreen*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
    }

    if (pThis) {
        return pThis->HandleMessage(hWnd, msg, wParam, lParam);
    }

    return DefWindowProcW(hWnd, msg, wParam, lParam);
}
