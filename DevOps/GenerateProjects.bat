@echo off
PUSHD .\

title Generate Projects (.bat)

:main
%cd%\Scripts\env\Scripts\python %cd%\Scripts\src\GenerateProjects.py

:exit
POPD
exit /b