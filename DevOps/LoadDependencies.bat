@echo off
PUSHD .\

title Load Dependencies (.bat)

:ask_for_admin_access
if not "%1"=="" goto :is_run_as_admin
echo Need administrator access.
powershell start -verb "runas %0 %cd%"
exit /b

:is_run_as_admin
cd /d "%1"

:python_check
echo Checks if Python is installed

python -V
if %errorlevel% EQU 0 goto :python_venv
echo Python does not installed!
pause
goto :exit

:python_venv
echo Load Dependencies

echo Deletes the folders "venv" and "__pycache__"
rd /s /q %cd%\Scripts\venv
rd /s /q %cd%\Scripts\src\Utilities\__pycache__

echo Config "venv"
python -m venv %cd%\Scripts\venv

:python_pip_dependencies
echo Install pip's Dependencies
%cd%\Scripts\venv\Scripts\python.exe -m pip install --upgrade pip
%cd%\Scripts\venv\Scripts\python.exe -m pip3 install --upgrade pip3
%cd%\Scripts\venv\Scripts\pip3 install requests
%cd%\Scripts\venv\Scripts\pip3 install GitPython

:main
%cd%\Scripts\venv\Scripts\python %cd%\Scripts\src\LoadDependencies.py

:exit
POPD
exit /b