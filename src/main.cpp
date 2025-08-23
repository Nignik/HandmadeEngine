#include "Platform/Windows/Window.h"

static bool running = false;

static Window wnd;

LRESULT CALLBACK win32WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  LRESULT result = 0;

  switch (uMsg) {
    case WM_SIZE:
      wnd.ResizeDIBSection();
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
    default:
      result = DefWindowProc(hWnd, uMsg, wParam, lParam);
      break;
  }

  return result;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
  WNDCLASSA windowClass = {};
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
  while (running) {
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0) {
      if (msg.message == WM_QUIT) {
        running = false;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    wnd.ResizeDIBSection();
    wnd.PaintWindow({255, 0, 0, 255});
    wnd.UpdateWindow();
  }
}