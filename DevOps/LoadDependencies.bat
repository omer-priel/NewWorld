@echo off
PUSHD .\

title LoadDependencies (.bat)
:python_check
echo Check if Python installed

python -V
if %errorlevel% EQU 0 goto :python_venv
echo Python do not installed!
pause
goto :exit

:python_venv
echo Load Dependencies

echo Delete "venv"
rd /s /q %cd%\Scripts\venv

echo Config "venv"
python -m venv %cd%\Scripts\venv

:python_pip_dependencies
echo Install pip Dependencies
%cd%\Scripts\venv\Scripts\python.exe -m pip install --upgrade pip
%cd%\Scripts\venv\Scripts\pip install requests
%cd%\Scripts\venv\Scripts\pip install GitPython

:main
%cd%\Scripts\venv\Scripts\python %cd%\Scripts\src\LoadDependencies.py

pause

:exit
POPD
exit /b