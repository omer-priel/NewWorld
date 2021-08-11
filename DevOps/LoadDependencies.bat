@echo off
PUSHD ..\

python -V
cls
if %errorlevel% EQU 0 goto :stage_1
echo Python do not installed!
pause
goto :exit

:stage_1
pip install -r \PIP_Dependencies.txt

:stage_2
echo Delete "Dependencies"
rd /s /q .\Dependencies

echo Load Submodules
git submodule init
git submodule update

md "Dependencies/bin"

:stage_3
echo Create Premake
cd .\Dependencies\Premake
start /MIN /WAIT cmd /c ".\Bootstrap.bat&exit"
cd ..
copy /y .\Premake\bin\release\premake5.exe .\bin\premake5.exe

:exit
POPD
exit /b