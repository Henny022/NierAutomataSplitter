@echo off
cd %~dp0
mkdir ..\vs2017-cmake 2> nul
cd ..\vs2017-cmake

cmake ..\cmake -G "Visual Studio 15 2017" -A x64
pause
