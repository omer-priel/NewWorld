@echo off
PUSHD ..\

:main
python DevOps\Scripts\src\Actions\GenerateProjects.py

:exit
POPD
exit /b