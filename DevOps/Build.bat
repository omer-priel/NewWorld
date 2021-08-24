@echo off
PUSHD .\

title Build (.bat)

:main
%cd%\Scripts\venv\Scripts\python %cd%\Scripts\src\Build.py

:exit
POPD
exit /b