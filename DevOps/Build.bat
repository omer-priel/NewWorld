@echo off
PUSHD .\

:main
%cd%\Scripts\venv\Scripts\python %cd%\Scripts\src\Build.py

:exit
POPD
exit