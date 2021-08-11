@echo off
PUSHD ..\

call Dependencies\bin\premake5.exe vs2019 --file=Solution.build.lua
PAUSE

:exit
POPD
exit /b