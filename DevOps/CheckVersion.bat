@echo off
PUSHD .\

title Check Version (.bat)

:main
%cd%\Scripts\venv\Scripts\python %cd%\Scripts\src\CheckVersion.py

:exit
POPD
exit /b