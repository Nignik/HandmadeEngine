@echo off

@echo off
setlocal

echo Configuring project with CMake...
cmake --preset debug
if errorlevel 1 (
  echo CMake configuration failed!
  pause
  exit /b 1
)

echo Building project...
cmake --build --preset debug
if errorlevel 1 (
  echo Build failed!
  pause
  exit /b 1
)

echo Build completed successfully!