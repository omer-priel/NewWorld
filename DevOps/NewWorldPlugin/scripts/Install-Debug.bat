@echo off

:ask_for_admin_access
if not "%1"=="" goto :is_run_as_admin
echo Need administrator access.
powershell start -verb "runas %0 %cd%"
exit /b

:is_run_as_admin
cd /d "%1"

cd ..\bin\Debug
NewWorldPlugin install-extension

:exit
exit /b