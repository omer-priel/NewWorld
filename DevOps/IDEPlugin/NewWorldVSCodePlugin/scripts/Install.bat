@echo off

cd ..
set /p version=Version: 
code --install-extension newworld-%version%.vsix

:exit
exit /b