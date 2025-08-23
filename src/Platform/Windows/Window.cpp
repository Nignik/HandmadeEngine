#include "Platform/Windows/Window.h"

void Window::InitWindow(HWND wndHandle) { 
  wndHandle_ = wndHandle;
}

void Window::ResizeDIBSection() {
  RECT wndRect;
  GetClientRect(wndHandle_, &wndRect);
  int w = wndRect.right - wndRect.left;
  int h = wndRect.bottom - wndRect.top;

  if (bitmap_.memory) {
    VirtualFree(bitmap_.memory, 0, MEM_RELEASE);
  }

  bitmap_.info.bmiHeader.biSize = sizeof(bitmap_.info.bmiHeader);
  bitmap_.info.bmiHeader.biWidth = w;
  bitmap_.info.bmiHeader.biHeight = -h;
  bitmap_.info.bmiHeader.biPlanes = 1;
  bitmap_.info.bmiHeader.biBitCount = 32;
  bitmap_.info.bmiHeader.biCompression = BI_RGB;

  bitmap_.width = w;
  bitmap_.height = h;

  int bytesPerPixel = 4;
  int bitmapMemorySize = (w * h) * bytesPerPixel;
  bitmap_.memory = VirtualAlloc(nullptr, bitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);
}

void Window::UpdateWindow() { 
  deviceCtx_ = GetDC(wndHandle_);
  RECT wndRect;
  GetClientRect(wndHandle_, &wndRect);
  int w = wndRect.right - wndRect.left;
  int h = wndRect.bottom - wndRect.top;
  StretchDIBits(deviceCtx_, 0, 0, w, h, 0, 0, bitmap_.width, bitmap_.height, bitmap_.memory, &bitmap_.info, DIB_RGB_COLORS, SRCCOPY); 
  ReleaseDC(wndHandle_, deviceCtx_);
}

void Window::PaintWindow(Pixel color) {
  Pixel* pixel = (Pixel*)bitmap_.memory;
  for (int row = 0; row < bitmap_.height; row++) {
    for (int col = 0; col < bitmap_.width; col++) {
      *pixel = color;
      pixel++;
    }
  }
}

[[nodiscard]] HWND Window::GetHandle() const { return wndHandle_; }
