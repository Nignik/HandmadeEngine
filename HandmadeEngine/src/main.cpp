#include <windows.h>

void paintWindow(HWND hWnd, DWORD color)
{
    PAINTSTRUCT paint;
    HDC deviceCtx = BeginPaint(hWnd, &paint);
    int x = paint.rcPaint.left;
    int y = paint.rcPaint.top;
    int w = paint.rcPaint.right - x;
    int h = paint.rcPaint.bottom - y;
    PatBlt(deviceCtx, x, y, w, h, color);
    EndPaint(hWnd, &paint);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    switch(uMsg)
    {
        case WM_SIZE:
            OutputDebugStringA("WM_SIZE\n");
            break;
        case WM_DESTROY:
            OutputDebugStringA("WM_DESTROY\n");
            break;
        case WM_CLOSE:
            OutputDebugStringA("WM_CLOSE\n");
            break;
        case WM_ACTIVATEAPP:
            OutputDebugStringA("WM_ACTIVATEAPP\n");
            break;
        case WM_PAINT:
            paintWindow(hWnd, BLACKNESS);
            break;
        default:
            result = DefWindowProc(hWnd, uMsg, wParam, lParam);
            break;
    }

    return result;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    WNDCLASS windowClass = {};
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WndProc;
    windowClass.hInstance = hInstance;
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.lpszClassName = "Handmade Engine";

    RegisterClass(&windowClass);
    HWND hWindow = CreateWindowEx(0, windowClass.lpszClassName, "Handmade Engine", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}