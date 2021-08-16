@echo off
PUSHD ..\

:main
python DevOps\Scripts\src\Actions\Build.py

:exit
POPD
exit /b