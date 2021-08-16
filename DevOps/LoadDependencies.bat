@echo off
PUSHD .\

title LoadDependencies (.bat)
:python_check
python -V
cls
if %errorlevel% EQU 0 goto :python_venv
echo Python do not installed!
pause
goto :exit

:python_venv
echo Delete "venv"
rd /s /q %cd%\DevOps\Scripts\venv

echo Config "venv"
python -m venv %cd%\DevOps\Scripts\venv

:python_pip_dependencies
echo Install pip Dependencies
%cd%\DevOps\Scripts\venv\Scripts\python.exe -m pip install --upgrade pip
%cd%\DevOps\Scripts\venv\Scripts\pip install requests
%cd%\DevOps\Scripts\venv\Scripts\pip install GitPython

:main
%cd%\DevOps\Scripts\venv\Scripts\python %cd%\DevOps\Scripts\src\Actions\LoadDependencies.py

:exit
POPD
exit /b