@echo off
PUSHD .\

title Fix Git Indexs

:main
cd ..
git rm --cached -r .
git add .

pause

:exit
POPD
exit /b