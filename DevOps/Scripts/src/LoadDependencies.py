"""

:stage_2
echo Delete "Dependencies"
rd /s /q .\Dependencies

echo Load Submodules
git submodule init
git submodule update

md "Dependencies/bin"

:stage_3
echo Create Premake
cd .\Dependencies\Premake
start /MIN /WAIT cmd /c ".\Bootstrap.bat&exit"
cd ..
copy /y .\Premake\bin\release\premake5.exe .\bin\premake5.exe

"""

# LoadDependencies - Load the basic solution dependencies

import Utilities.Utilities as Utilities

import json
import git
import os

Utilities.SetTitle("Load Dependencies")

# Check is programs exists
try:
    os.system('start /wait /min cmd /c "(npm --version)&exit"')
except:
	print("npm dos not exists!")
	Utilities.ExitAction()

os.system("title Load Dependencies")

print("Install NewWorldVSCodePlugin Dependencies")
newWorldVSCodePlugin_folder = Utilities.GetSubPath("DevOps\\IDEPlugin\\NewWorldVSCodePlugin");

os.removedirs(f"{newWorldVSCodePlugin_folder}/node_modules")

os.system(f"cd {newWorldVSCodePlugin_folder}& start /wait /min npm install")

Utilities.PresToConinue()