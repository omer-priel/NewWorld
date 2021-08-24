@echo off

cd ..
set /p version=Version: 
copy /y .\bin\Debug\NewWorldVisualStudioPlugin.vsix .\NewWorld-%version%.vsix

:exit
exit /b