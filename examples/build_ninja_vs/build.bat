@echo off
setlocal
cd build%~1
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat"
ninja SFMLEngineTest
if %errorlevel% neq 0 cd .. && exit /b %errorlevel%
cd ..
endlocal