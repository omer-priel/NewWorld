@echo off
PUSHD .\

python Scripts\src\Actions\CheckVersion.py

POPD
exit /b