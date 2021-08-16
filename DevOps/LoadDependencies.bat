@echo off
PUSHD ..\

:python_check
python -V
cls
if %errorlevel% EQU 0 goto :python_pip_dependencies
echo Python do not installed!
pause
goto :exit

:python_venv

:python_pip_dependencies
echo Install pip Dependencies
python.exe -m pip install --upgrade pip
pip install requests
pip install GitPython

:main
python DevOps\Scripts\src\Actions\LoadDependencies.py

:exit
POPD
exit /b