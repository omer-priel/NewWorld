@echo off

cd ..
set app="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\VSIXInstaller.exe"

cd bin\Release
"%app%" /quiet /uninstall:NewWorldVisualStudioPlugin.a10ed3bf-f287-4558-82c3-852a1aa80f11

:exit
exit /b