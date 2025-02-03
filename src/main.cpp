#include "../include/LoginScreen.h"

int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PWSTR lpCmdLine,
    int nCmdShow
) {
    CLoginScreen loginScreen(hInstance);

    if (!loginScreen.Create()) {
        MessageBoxW(nullptr, L"Pencere oluşturulamadı!", L"Hata", MB_ICONERROR);
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