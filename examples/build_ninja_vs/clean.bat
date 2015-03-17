@echo off
setlocal
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat"
cd build%~1
ninja clean
cd ..
endlocal