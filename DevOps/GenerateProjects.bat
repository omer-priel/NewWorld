@echo off
PUSHD .\

echo %cd%
pause

:main
%cd%\Scripts\venv\Scripts\python %cd%\Scripts\src\GenerateProjects.py

:exit
POPD
exit