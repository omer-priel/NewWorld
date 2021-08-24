@echo off

cd ..
set app="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\VSIXInstaller"

cd bin\Release
%app% /quiet NewWorldVisualStudioPlugin.vsix

:exit
exit /b