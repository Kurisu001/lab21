#include <windows.h>
#include <string>
#include <sstream>

// ประกาศฟังก์ชัน Window Procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

char textA[100];
char textB[100];
HWND InA;
HWND InB;
HWND Plusbtn;
HWND Minusbtn;
HWND Multiplybtn;
HWND Divbtn;
long long a, b;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 1. กำหนดคลาสหน้าต่าง
    const char CLASS_NAME[] = "MyWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc; // กำหนดฟังก์ชันจัดการข้อความ
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(255, 55, 60));

    RegisterClass(&wc);

    // 2. สร้างหน้าต่างหลัก
    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, "Calculator", WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200,
        NULL, NULL, hInstance, NULL);
    Plusbtn = CreateWindow(
        "BUTTON", "+", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        50 + 15, 130, 20, 20, hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
    Minusbtn = CreateWindow(
        "BUTTON", "-", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        80 + 15, 130, 20, 20, hwnd, (HMENU)2, GetModuleHandle(NULL), NULL);
    Multiplybtn = CreateWindow(
        "BUTTON", "*", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        110 + 15, 130, 20, 20, hwnd, (HMENU)3, GetModuleHandle(NULL), NULL);
    Divbtn = CreateWindow(
        "BUTTON", "/", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        140 + 15, 130, 20, 20, hwnd, (HMENU)4, GetModuleHandle(NULL), NULL);
    InA = CreateWindowEx(
        0, "EDIT", "",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        20, 50, 200, 25, hwnd, (HMENU)6, GetModuleHandle(NULL), NULL);
    InB = CreateWindowEx(
        0, "EDIT", "",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
        20, 80, 200, 25, hwnd, (HMENU)7, GetModuleHandle(NULL), NULL);

    if (hwnd == NULL)
        return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // 3. วนลูปรับข้อความ
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// 4. ฟังก์ชันจัดการข้อความของหน้าต่าง
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case 1: // Plus button
        case 2: // Minus button
        case 3: // Multiply button
        case 4: // Divide button
        {
            int gwtstat = GetWindowText(InA, textA, 100);
            int gwtstat2 = GetWindowText(InB, textB, 100);
            if (gwtstat > 0 && gwtstat2 > 0)
            {
                a = atoi(textA);
                b = atoi(textB);
                long long result = 0;
                std::stringstream ss;
                switch (LOWORD(wParam))
                {
                case 1:
                    result = a + b;
                    break;
                case 2:
                    result = a - b;
                    break;
                case 3:
                    result = a * b;
                    break;
                case 4:
                    if (b != 0)
                        result = a / b;
                    else
                        MessageBox(hwnd, "Cannot divide by zero", "Error", MB_OK | MB_ICONERROR);
                    break;
                }
                ss << result;
                MessageBox(hwnd, ss.str().c_str(), "Result", MB_OK);
            }
            break;
        }
        }
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        TextOut(hdc, 85, 20, "Calculator", 10);
        EndPaint(hwnd, &ps);
        return 0;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}