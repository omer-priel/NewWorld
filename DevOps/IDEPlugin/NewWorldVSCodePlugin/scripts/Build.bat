@echo off

cd ..
vsce package

:exit
POPD
exit /b