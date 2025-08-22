#include <windows.h>

#include "Shapes.h"

static bool running = false;

class Window
{
public:
    Window() = default;
    
    void InitWindow(HWND wndHandle)
    {
        mWndHandle = wndHandle;
    }

    void ResizeDIBSection()
    {
        RECT wndRect;
        GetClientRect(mWndHandle, &wndRect);
        int w = wndRect.right - wndRect.left;
        int h = wndRect.bottom - wndRect.top;

        if (mBitmapHandle)
        {
            DeleteObject(mBitmapHandle);
        }

        mBitmapInfo.bmiHeader.biSize = sizeof(mBitmapInfo.bmiHeader);
        mBitmapInfo.bmiHeader.biWidth = w;
        mBitmapInfo.bmiHeader.biHeight = h;
        mBitmapInfo.bmiHeader.biPlanes = 1;
        mBitmapInfo.bmiHeader.biBitCount = 32;
        mBitmapInfo.bmiHeader.biCompression = BI_RGB;

        mDeviceCtx = CreateCompatibleDC(nullptr);
        mBitmapHandle = CreateDIBSection(mDeviceCtx, &mBitmapInfo, DIB_RGB_COLORS, &mBitmapMemory, nullptr, 0);
    }

    void UpdateWindow(otac::Rect wndRect)
    {
        StretchDIBits(mDeviceCtx, wndRect.x, wndRect.y, wndRect.w, wndRect.h, wndRect.x, wndRect.y, wndRect.w, wndRect.h, mBitmapMemory, &mBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
    }

    void PaintWindow(DWORD color)
    {
        PAINTSTRUCT paint;
        HDC deviceCtx = BeginPaint(mWndHandle, &paint);
        int x = paint.rcPaint.left;
        int y = paint.rcPaint.top;
        int w = paint.rcPaint.right - x;
        int h = paint.rcPaint.bottom - y;
        PatBlt(deviceCtx, x, y, w, h, color);
        EndPaint(mWndHandle, &paint);
    }

    [[nodiscard]] HWND GetHandle() const
    {
        return mWndHandle;
    }

private:
    HWND mWndHandle;
    BITMAPINFO mBitmapInfo;
    void* mBitmapMemory;
    HBITMAP mBitmapHandle;
    HDC mDeviceCtx;
};

static Window wnd;

LRESULT CALLBACK win32WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    switch(uMsg)
    {
        case WM_SIZE:
            OutputDebugStringA("WM_SIZE\n");
            break;
        case WM_DESTROY:
            running = false;
            break;
        case WM_CLOSE:
            running = false;
            break;
        case WM_ACTIVATEAPP:
            OutputDebugStringA("WM_ACTIVATEAPP\n");
            break;
        case WM_PAINT:
            wnd.PaintWindow(BLACKNESS);
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
	windowClass.lpfnWndProc = win32WndProc;
	windowClass.hInstance = hInstance;
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.lpszClassName = "Handmade Engine";

	RegisterClassA(&windowClass);
	HWND hWindow = CreateWindowExA(0, windowClass.lpszClassName, "Handmade Engine", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);
    
    wnd.InitWindow(hWindow);

    MSG msg;
    running = true;
    while (running && GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}