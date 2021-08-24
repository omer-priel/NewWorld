@echo off

cd ..
set /p version=Version: 
copy /y .\bin\Release\NewWorldVisualStudioPlugin.vsix .\NewWorld-%version%.vsix

:exit
exit /b