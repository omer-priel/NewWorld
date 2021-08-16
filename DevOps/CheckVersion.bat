@echo off
PUSHD .\

:main
%cd%\DevOps\Scripts\venv\Scripts\python %cd%\DevOps\Scripts\src\Actions\CheckVersion.py

:exit
POPD
exit /b