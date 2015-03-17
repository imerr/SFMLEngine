@echo off
setlocal
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat"
mkdir build
cd build
cmake -Wno-dev -G "Ninja" ../ProjectDir -DCMAKE_BUILD_TYPE=Debug
cd ..
mkdir buildrelease
cd buildrelease
cmake -Wno-dev -G "Ninja" ../ProjectDir -DCMAKE_BUILD_TYPE=Release
cd ..
endlocal