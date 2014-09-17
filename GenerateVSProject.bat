@echo off
set PATH=%PATH%;C:\MinGW\bin
echo Generatw IntWars Makefiles
echo ------------------------------
IF EXIST build GOTO BUILDDIR
ELSE GOTO MAIN 

:BUILDDIR
echo Build directory exists, removing...
rmdir /s /q build
GOTO MAIN

:MAIN
echo Recreating build directory...
mkdir build
cd build
echo Creating MinGW Makefiles...
echo ------------------------------
cmake .. -G "Visual Studio 12 2013"
cd ..
pause