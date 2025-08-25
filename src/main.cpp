#include "Platform/Windows/Window.h"

static bool running = false;

static Window* wnd;

LRESULT CALLBACK wnd_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  LRESULT result = 0;

  switch (uMsg) {
    case WM_SIZE:
      if (wnd != nullptr)
        wnd->ResizeDIBSection();
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

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow) {
  wnd = new Window(hInstance, iCmdShow, wnd_proc);

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
    wnd->ResizeDIBSection();
    wnd->PaintWindow({255, 0, 0, 255});
    wnd->UpdateWindow();
  }

  delete wnd;

  return msg.wParam;
}