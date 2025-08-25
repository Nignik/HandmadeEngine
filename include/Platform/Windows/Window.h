#include <windows.h>
#include <gdiplus.h>
#include <utility>

#include <ScopedPtr.h>


#pragma comment (lib,"Gdiplus.lib")

class Window {
public:
  Window(HINSTANCE hInstance, INT iCmdShow, WNDPROC wndProc);
  ~Window();

  void ResizeDIBSection();
  void UpdateWindow() const;
  void PaintWindow(const Gdiplus::Color& color);

  [[nodiscard]] HWND GetHandle() const;

private:
  HWND wndHandle_;
  Otac::ScopedPtr<Gdiplus::Bitmap> bitmap_;
  RECT wndRect_;
  ULONG_PTR gdiplusToken_;
};