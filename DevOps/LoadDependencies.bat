@echo off
PUSHD ..\
echo Delete "Dependencies"
rd /s /q .\Dependencies

echo Load Submodules
git submodule init
git submodule update

md "Dependencies/bin"

echo Create Premake
cd .\Dependencies\Premake
start /MIN /WAIT cmd /c ".\Bootstrap.bat&exit"
cd ..
copy /y .\Premake\bin\release\premake5.exe .\bin\premake5.exe
POPD