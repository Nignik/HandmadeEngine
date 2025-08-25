#include "Platform/Windows/Window.h"

#include <cstdio>

Window::Window(HINSTANCE hInstance, INT iCmdShow, WNDPROC wndProc)
{
  WNDCLASS wndClass = {};
  wndClass.style = CS_HREDRAW | CS_VREDRAW;
  wndClass.lpfnWndProc = wndProc;
  wndClass.hInstance = hInstance;
  wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wndClass.lpszClassName = TEXT("HandmadeEngine");
    
  RegisterClass(&wndClass);
  wndHandle_ = CreateWindow(wndClass.lpszClassName, TEXT("Handmade Engine"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);

  Gdiplus::GdiplusStartupInput gdiplusStartupInput;
  Gdiplus::GdiplusStartup(&gdiplusToken_, &gdiplusStartupInput, nullptr);
}

Window::~Window()
{
  delete bitmap_.Release();
  Gdiplus::GdiplusShutdown(gdiplusToken_);
}

void Window::ResizeDIBSection() {
  RECT wndRect;
  GetClientRect(wndHandle_, &wndRect);
  int w = wndRect.right - wndRect.left;
  int h = wndRect.bottom - wndRect.top;

  bitmap_ = Otac::ScopedPtr<Gdiplus::Bitmap>(w, h, PixelFormat32bppARGB);
}

void Window::UpdateWindow() const
{
  HDC hdc = GetDC(wndHandle_);
  Gdiplus::Graphics gfx(hdc);
  //gfx.Clear(Gdiplus::Color(0, 0, 0, 0));
  gfx.DrawImage(bitmap_.Get(), 0, 0);
  ReleaseDC(wndHandle_, hdc);
}

void Window::PaintWindow(const Gdiplus::Color& color) {
  for (int row = 0; row < bitmap_->GetHeight(); row++) {
    for (int col = 0; col < bitmap_->GetWidth(); col++) {
      bitmap_->SetPixel(col, row, color);
    }
  }
}

[[nodiscard]] HWND Window::GetHandle() const { return wndHandle_; }
