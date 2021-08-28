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
if %errorlevel% EQU 0 goto :python_env
echo Python does not installed!
pause
goto :exit

:python_env
set folder=%cd%\Scripts

echo Clean Scripts
rd /s /q %folder%\env
rd /s /q %folder%\src\Utilities\__pycache__

echo Create Virtual Environment of Scripts
python -m venv %folder%\env

echo Install pip's Dependencies
%folder%\env\Scripts\python.exe -m pip install --upgrade pip

%folder%\env\Scripts\python.exe -m pip install -r %folder%\requirements.txt

:main
%cd%\Scripts\env\Scripts\python %cd%\Scripts\src\LoadDependencies.py

:exit
POPD
exit /b