@echo off
PUSHD .\

title Check Version (.bat)

:main
%cd%\Scripts\env\Scripts\python %cd%\Scripts\src\CheckVersion.py

:exit
POPD
exit /b