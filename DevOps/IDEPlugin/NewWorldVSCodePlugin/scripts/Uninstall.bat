@echo off

cd ..
set /p version=Version:
code --uninstall-extension newworld.newworld

:exit
exit /b