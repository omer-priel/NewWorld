@echo off
PUSHD ..\

:main
python DevOps\Scripts\src\Actions\CheckVersion.py

:exit
POPD
exit /b