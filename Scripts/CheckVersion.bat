@echo off

REM TODO: Change CheckVersion to python file
REM       from CheckVersion.bat to CheckVersion.py
REM GitLab API: https://docs.gitlab.com/ee/api/commits.html

PUSHD ..\

set gitLab_ProjectID=28527190

for /f "tokens=* USEBACKQ" %%i IN (`git rev-parse --short HEAD`) DO (SET gitID=%%i )
ECHO %gitID%

set barnch=master
curl "https://gitlab.com/api/v4/projects/%gitLab_ProjectID%/repository/commits/%barnch%"
echo
pause

POPD
exit /b