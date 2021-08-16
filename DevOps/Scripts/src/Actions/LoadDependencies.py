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
import subprocess

Utilities.SetTitle("Load Dependencies")

# Check is programs exists
try:
    subprocess.call(["npm", "--version"])
except FileNotFoundError:
    # handle file not found error.

Utilities.PresToConinue()