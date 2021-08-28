@echo off

echo Install

set app="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\VSIXInstaller"

%app% /quiet ..\bin\Release\NewWorldVisualStudioExtension.vsix

:exit
exit /b