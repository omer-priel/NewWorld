@echo off

echo Publish

set /p version=Version: 
copy /y ..\bin\Release\NewWorldVisualStudioExtension.vsix ..\NewWorld-%version%.vsix

:exit
exit /b