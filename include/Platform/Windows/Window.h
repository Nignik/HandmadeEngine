#include <windows.h>

#include <cstdint>

#include "Shapes.h"

struct Bitmap {
  BITMAPINFO info;
  uint32_t width, height;
  void *memory;
};

struct Pixel {
  uint8_t r{0}, g{0}, b{0}, a{255};
};

class Window {
 public:
  Window() = default;

  void InitWindow(HWND wndHandle);
  void ResizeDIBSection();
  void UpdateWindow();
  void PaintWindow(Pixel color);

  [[nodiscard]] HWND GetHandle() const;

 private:
  HWND wndHandle_;
  HDC deviceCtx_;
  RECT wndRect_;
  Bitmap bitmap_;
};