@echo off
PUSHD .\

title CheckVersion (.bat)

:main
%cd%\Scripts\venv\Scripts\python %cd%\Scripts\src\CheckVersion.py

:exit
POPD
exit /b