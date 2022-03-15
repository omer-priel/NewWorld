@echo off

echo Uninstall

set app="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\VSIXInstaller"

%app% /uninstall:NewWorldVisualStudioExtension.a10ed3bf-f287-4558-82c3-852a1aa80f11

:exit
exit /b