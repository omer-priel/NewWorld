@echo off

cd ..

:main
%cd%\env\Scripts\python.exe -m pip freeze > requirements.txt

:exit
exit /b