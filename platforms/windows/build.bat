@echo off
echo Compile Begin!

set MINGW=D:\Basis-soft\mingw64\mingw64\bin
set PATH=%MINGW%;%PATH%
set PROJECT=%~dp0

echo MinGW Compiler Location Is %MINGW%
echo Project Location Is %Project%

cd %MINGW%

echo Cleaning....

del /q %PROJECT%\target
mkdir %PROJECT%\target

echo Building...

x86_64-w64-mingw32-g++ -Wall -DBUILD_DLL -O2  -c %project%\main.cpp -o %PROJECT%\target\main.o
x86_64-w64-mingw32-g++ -shared -Wl,--output-def=%PROJECT%\target\libJAria.def -Wl,--out-implib=%PROJECT%\target\libJAria.a -Wl,--dll  %PROJECT%\target\main.o  -o %PROJECT%\target\JAria.dll -s  %PROJECT%\libaria2.dll.a -luser32

echo Compile Complete.