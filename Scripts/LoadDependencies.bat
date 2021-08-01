@echo off
cd ..
echo Delete "Dependencies"
rd /s /q .\Dependencies

echo Load Submodules
git submodule init
git submodule update

echo Create Premake
cd .\Dependencies\Premake
start /MIN /WAIT cmd /c "Bootstrap.bat&exit"
copy /y .\bin\release\premake5.exe premake.exe