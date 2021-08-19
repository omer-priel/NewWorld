@echo off
PUSHD .\

:main
%cd%\Scripts\venv\Scripts\python %cd%\Scripts\src\CheckVersion.py

:exit
POPD
exit /b