#include <windows.h>
#include <string>
#include <sstream>
#include <iostream>
HWND textfeild, plu, min, mul, divi, num1, num2;
void ShowResult(HWND hwnd, double result) {
    std::ostringstream oss;
    oss << result;
    MessageBox(hwnd, oss.str().c_str(), "Result", MB_OK);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message) {
        case WM_CREATE: {
            textfeild = CreateWindow("STATIC",
                                     "Please input two numbers",
                                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                                     16, 16, 200, 25,
                                     hwnd, NULL, NULL, NULL);
            num1 = CreateWindow("EDIT",
                                "",
                                WS_VISIBLE | WS_CHILD | WS_BORDER,
                                16, 40, 200, 25,
                                hwnd, (HMENU)9, NULL, NULL);
            num2 = CreateWindow("EDIT",
                                "",
                                WS_VISIBLE | WS_CHILD | WS_BORDER,
                                16, 64, 200, 25,
                                hwnd, (HMENU)10, NULL, NULL);
            plu = CreateWindow("BUTTON",
                               "+",
                               WS_VISIBLE | WS_CHILD | WS_BORDER,
                               50, 100, 25, 25,
                               hwnd, (HMENU)1, NULL, NULL);
            min = CreateWindow("BUTTON",
                               "-",
                               WS_VISIBLE | WS_CHILD | WS_BORDER,
                               85, 100, 25, 25,
                               hwnd, (HMENU)2, NULL, NULL);
            mul = CreateWindow("BUTTON",
                               "*",
                               WS_VISIBLE | WS_CHILD | WS_BORDER,
                               120, 100, 25, 25,
                               hwnd, (HMENU)3, NULL, NULL);
            divi = CreateWindow("BUTTON",
                                "/",
                                WS_VISIBLE | WS_CHILD | WS_BORDER,
                                155, 100, 25, 25,
                                hwnd, (HMENU)4, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            char x1[256], y1[256];
            GetWindowText(num1, x1, 255);
            GetWindowText(num2, y1, 255);
            double fnum = atof(x1);
            double Snum = atof(y1);
            double result = 0.0;
            switch (LOWORD(wParam)) {
                case 1:
                    result = fnum + Snum;
                    ShowResult(hwnd, result);
                    break;
                case 2:
                    result = fnum - Snum;
                    ShowResult(hwnd, result);
                    break;
                case 3:
                    result = fnum * Snum;
                    ShowResult(hwnd, result);
                    break;
                case 4:
                    result = fnum / Snum;
                    ShowResult(hwnd, result);
                    break;
            }
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground=(HBRUSH)(COLOR_WINDOW+25);
    wc.lpszClassName = "WindowClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,
                          "WindowClass",
                          "My Calculator",
                          WS_VISIBLE | WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          250,
                          200,
                          NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}
