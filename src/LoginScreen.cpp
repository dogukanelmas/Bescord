#include "../include/LoginScreen.h"
#include <windowsx.h>

CLoginScreen::CLoginScreen(HINSTANCE hInstance) : m_hInstance(hInstance), m_hWnd(nullptr), screen(true) {}

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
        MessageBoxW(nullptr, L"Pencere sınıfı kaydedilemedi!", L"Hata", MB_ICONERROR);
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

void CLoginScreen::CreateLoginUI(HWND hWnd) {
    CreateWindowExW(0, L"STATIC", L" WELCOME", WS_CHILD | WS_VISIBLE,
        (winX - 80) / 2, winY / 2 - 155, 80, 22, hWnd, nullptr, nullptr, nullptr);

    CreateWindowExW(0, L"STATIC", L"   User Name", WS_CHILD | WS_VISIBLE,
        (winX - 300) / 2, winY / 2 - 75, 110, 20, hWnd, nullptr, nullptr, nullptr);
    boxName = CreateWindowExW(0, L"EDIT", nullptr, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
        (winX - 300) / 2, winY / 2 - 50, 300, 20, hWnd, nullptr, nullptr, nullptr);

    CreateWindowExW(0, L"STATIC", L"   Password", WS_CHILD | WS_VISIBLE,
        (winX - 300) / 2, winY / 2 - 15, 100, 20, hWnd, nullptr, nullptr, nullptr);
    boxPassword = CreateWindowExW(0, L"EDIT", nullptr, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_PASSWORD,
        (winX - 300) / 2, winY / 2 + 10, 300, 20, hWnd, nullptr, nullptr, nullptr);

    boxForgat = CreateWindowExW(WS_EX_CLIENTEDGE, L"BUTTON", L"Forgat Password", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        (winX / 2 + 35) , (winY - 20) / 2 + 40, 115, 24, hWnd, (HMENU)3, nullptr, nullptr);

    loginButton = CreateWindowExW(WS_EX_CLIENTEDGE, L"BUTTON", L" Login", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        (winX - 95) / 2, winY / 2 + 100, 95, 30, hWnd, (HMENU)1, nullptr, nullptr);

    CreateWindowExW(0, L"STATIC", L"    Need an account?\t  ----->", WS_CHILD | WS_VISIBLE,
        0, winY - 20, winX, 20, hWnd, nullptr, nullptr, nullptr);
    click = CreateWindowExW(WS_EX_CLIENTEDGE, L"BUTTON", L"CLICK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        winX / 2 + 80, (winY - 21) , 95, 22, hWnd, (HMENU)2, nullptr, nullptr);
}

void CLoginScreen::CreateRegisterUI(HWND hWnd) {
    CreateWindowExW(0, L"STATIC", L" WELCOME", WS_CHILD | WS_VISIBLE,
        (winX - 80) / 2, winY / 2 - 155, 80, 22, hWnd, nullptr, nullptr, nullptr);

    CreateWindowExW(0, L"STATIC", L"New User Name", WS_CHILD | WS_VISIBLE,
        (winX - 300) / 2, winY / 2 - 75, 110, 20, hWnd, nullptr, nullptr, nullptr);
    boxName = CreateWindowExW(0, L"EDIT", nullptr, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
        (winX - 300) / 2, winY / 2 - 50, 300, 20, hWnd, nullptr, nullptr, nullptr);

    CreateWindowExW(0, L"STATIC", L"New Password", WS_CHILD | WS_VISIBLE,
        (winX - 300) / 2, winY / 2 - 15, 100, 20, hWnd, nullptr, nullptr, nullptr);
    boxPassword = CreateWindowExW(0, L"EDIT", nullptr, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_PASSWORD,
        (winX - 300) / 2, winY / 2 + 10, 300, 20, hWnd, nullptr, nullptr, nullptr);

    loginButton = CreateWindowExW(WS_EX_CLIENTEDGE, L"BUTTON", L" Sign Up", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        (winX - 95) / 2, winY / 2 + 100, 95, 30, hWnd, (HMENU)1, nullptr, nullptr);

    CreateWindowExW(0, L"STATIC", L"    I have an account\t  ----->", WS_CHILD | WS_VISIBLE,
        0, winY - 20, winX, 20, hWnd, nullptr, nullptr, nullptr);
    click = CreateWindowExW(WS_EX_CLIENTEDGE, L"BUTTON", L"CLICK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        winX / 2 + 80, (winY - 21), 95, 22, hWnd, (HMENU)2, nullptr, nullptr);
}

LRESULT CLoginScreen::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        if (screen) {
            CreateLoginUI(hWnd);
        }
        else {
            CreateRegisterUI(hWnd);
        }
        break;

    case WM_COMMAND:
        wchar_t name[128];
        wchar_t password[128];
        if (wParam == 1) {
            GetWindowText(boxName, name, 128);
            GetWindowText(boxPassword, password, 128);

            // MainScreen'i oluştur
            CMainScreen* pMainScreen = new CMainScreen(m_hInstance);
            if (!pMainScreen->Create()) {
                MessageBoxW(nullptr, L"Main Screen oluşturulamadı!", L"Hata", MB_ICONERROR);
                delete pMainScreen;
                return 0;
            }
            pMainScreen->Show(SW_SHOW);

            // LoginScreen'i gizle ve sonrasında yok et
            ShowWindow(m_hWnd, SW_HIDE);
            DestroyWindow(m_hWnd);
        }

        if (wParam == 2) {
            DestroyWindow(boxName);
            DestroyWindow(boxPassword);
            DestroyWindow(loginButton);
            DestroyWindow(click);
            if(boxForgat) DestroyWindow(boxForgat);
            screen = !screen;
            if (screen) {
                CreateLoginUI(hWnd);
            }
            else {
                CreateRegisterUI(hWnd);
            }
        }
        if (wParam == 3) {
            GetWindowText(boxName, name, 128);
            MessageBox(NULL, name, L"yarrağımı ye, unutmasaydın", ES_CENTER);
        }
        break;

    case WM_KEYDOWN:

        if (wParam == VK_ESCAPE) PostQuitMessage(0);

        break;

    case WM_DESTROY:

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
