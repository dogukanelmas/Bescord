#include "../include/MainScreen.h"
#include <windowsx.h>

CMainScreen::CMainScreen(HINSTANCE hInstance) : m_hInstance(hInstance), m_hWnd(nullptr) {}

CMainScreen::~CMainScreen() {
    if (m_hWnd) DestroyWindow(m_hWnd);
}

bool CMainScreen::Create() {
    WNDCLASSEXW wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = CMainScreen::WndProc;
    wc.hInstance = m_hInstance;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 8);
    wc.lpszClassName = m_className.c_str();

    if (!RegisterClassExW(&wc)) {
        MessageBoxW(nullptr, L"Main Screen sınıfı kaydedilemedi!", L"Hata", MB_ICONERROR);
        return false;
    }

    m_hWnd = CreateWindowExW(
        0,
        m_className.c_str(),
        L"Ana Ekran",
        WS_POPUP,
        (GetSystemMetrics(SM_CXSCREEN) - 1280) / 2,
        (GetSystemMetrics(SM_CYSCREEN) - 720) / 2, 1280, 720,
        nullptr,
        nullptr,
        m_hInstance,
        this
    );

    return m_hWnd != nullptr;
}

void CMainScreen::Show(int nCmdShow) {
    ShowWindow(m_hWnd, nCmdShow);
    UpdateWindow(m_hWnd);
}

void CMainScreen::AdjustComponents(HWND hWnd) {
    RECT rect;
    GetClientRect(hWnd, &rect);

    int buttonSize = 40;

    // Üst köşe butonlarını yerleştir
    MoveWindow(hMinimizeButton, rect.right - (3 * buttonSize), 10, buttonSize, buttonSize, TRUE);
    MoveWindow(hFullscreenButton, rect.right - (2 * buttonSize), 10, buttonSize, buttonSize, TRUE);
    MoveWindow(hCloseButton, rect.right - buttonSize, 10, buttonSize, buttonSize, TRUE);

    // Sunucu listesi yerleşimi
    MoveWindow(hServerList, 70, 50, rect.right / 4, rect.bottom - 50, TRUE);

    // Sunucu ekleme ve yaratma butonları
    MoveWindow(hAddServerButton, 10, rect.bottom / 2 - 40, buttonSize, buttonSize, TRUE);
    MoveWindow(hCreateServerButton, 10, rect.bottom / 2, buttonSize, buttonSize, TRUE);

    // Sohbet alanı ve mesaj girişi yerleşimi
    int chatAreaWidth = rect.right - (rect.right / 4) - 140;
    int chatAreaHeight = rect.bottom - 120;
    MoveWindow(hChatArea, rect.right / 4 + 80, 50, chatAreaWidth, chatAreaHeight, TRUE);

    int inputHeight = 30;
    MoveWindow(hMessageInput, rect.right / 4 + 80, rect.bottom - inputHeight - 10, chatAreaWidth - 50, inputHeight, TRUE);

    // Gönder butonu
    MoveWindow(hSendButton, rect.right - 50, rect.bottom - inputHeight - 10, 40, inputHeight, TRUE);
}

LRESULT CMainScreen::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        HFONT hFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");

        RECT rect;
        GetClientRect(hWnd, &rect);

        int buttonSize = 40;

        // Pencere kontrol butonları
        hMinimizeButton = CreateWindowEx(0, L"BUTTON", L"_", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rect.right - (3 * buttonSize), 10, buttonSize, buttonSize, hWnd, (HMENU)3, nullptr, nullptr);
        SendMessage(hMinimizeButton, WM_SETFONT, (WPARAM)hFont, TRUE);

        hFullscreenButton = CreateWindowEx(0, L"BUTTON", L"?", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rect.right - (2 * buttonSize), 10, buttonSize, buttonSize, hWnd, (HMENU)2, nullptr, nullptr);
        SendMessage(hFullscreenButton, WM_SETFONT, (WPARAM)hFont, TRUE);

        hCloseButton = CreateWindowEx(0, L"BUTTON", L"X", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rect.right - buttonSize, 10, buttonSize, buttonSize, hWnd, (HMENU)1, nullptr, nullptr);
        SendMessage(hCloseButton, WM_SETFONT, (WPARAM)hFont, TRUE);

        // Sunucu listesi
        hServerList = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", nullptr, WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY, 70, 50, rect.right / 4, rect.bottom - 50, hWnd, nullptr, nullptr, nullptr);
        SendMessage(hServerList, WM_SETFONT, (WPARAM)hFont, TRUE);

        // Sunucu ekleme ve yaratma butonları
        hAddServerButton = CreateWindowEx(0, L"BUTTON", L"+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, rect.bottom / 2 - 40, buttonSize, buttonSize, hWnd, (HMENU)4, nullptr, nullptr);
        SendMessage(hAddServerButton, WM_SETFONT, (WPARAM)hFont, TRUE);

        hCreateServerButton = CreateWindowEx(0, L"BUTTON", L"31", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, rect.bottom / 2, buttonSize, buttonSize, hWnd, (HMENU)5, nullptr, nullptr);
        SendMessage(hCreateServerButton, WM_SETFONT, (WPARAM)hFont, TRUE);

        // Sohbet alanı
        hChatArea = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", nullptr, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY, rect.right / 4 + 80, 50, rect.right - (rect.right / 4) - 140, rect.bottom - 120, hWnd, nullptr, nullptr, nullptr);
        SendMessage(hChatArea, WM_SETFONT, (WPARAM)hFont, TRUE);

        // Mesaj girişi
        hMessageInput = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", nullptr, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL, rect.right / 4 + 80, rect.bottom - 40, rect.right - (rect.right / 4) - 190, 30, hWnd, (HMENU)6, nullptr, nullptr);
        SendMessage(hMessageInput, WM_SETFONT, (WPARAM)hFont, TRUE);

        // Gönder butonu
        hSendButton = CreateWindowEx(0, L"BUTTON", L"Gönder", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rect.right - 100, rect.bottom - 40, 90, 30, hWnd, (HMENU)7, nullptr, nullptr);
        SendMessage(hSendButton, WM_SETFONT, (WPARAM)hFont, TRUE);

        break;
    }

    case WM_SIZE:
        AdjustComponents(hWnd);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) { // Kapat butonu
            DestroyWindow(hWnd);
        }
        else if (LOWORD(wParam) == 2) { // Tam ekran butonu
            ShowWindow(hWnd, IsZoomed(hWnd) ? SW_RESTORE : SW_MAXIMIZE);
        }
        else if (LOWORD(wParam) == 3) { // Küçült butonu
            ShowWindow(hWnd, SW_MINIMIZE);
        }
        else if (LOWORD(wParam) == 4) { // Sunucu ekleme butonu
            // Sunucu ekleme işlemleri burada yapılacak
        }
        else if (LOWORD(wParam) == 5) { // Sunucu oluşturma butonu
            // Sunucu oluşturma işlemleri burada yapılacak
        }
        else if (LOWORD(wParam) == 7) { // Gönder butonu
            wchar_t message[256];
            GetWindowText(hMessageInput, message, 256);
            if (wcslen(message) > 0) {
                SendMessage(hChatArea, EM_REPLACESEL, 0, (LPARAM)(std::wstring(message) + L"\r\n").c_str());
                SetWindowText(hMessageInput, L"");
            }
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

LRESULT CALLBACK CMainScreen::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    CMainScreen* pThis = nullptr;

    if (msg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = reinterpret_cast<CMainScreen*>(pCreate->lpCreateParams);
        SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
        pThis->m_hWnd = hWnd;
    }
    else {
        pThis = reinterpret_cast<CMainScreen*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
    }

    if (pThis) {
        return pThis->HandleMessage(hWnd, msg, wParam, lParam);
    }

    return DefWindowProcW(hWnd, msg, wParam, lParam);
}