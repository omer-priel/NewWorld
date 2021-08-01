@echo off
PUSHD ..\
call Dependencies\bin\premake5.exe vs2019 --file=Solution.build.lua
POPD
REM if %errorlevel% EQU 0 goto :exit
PAUSE
:exit
exit /b