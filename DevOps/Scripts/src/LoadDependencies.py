# LoadDependencies - Load the basic solution dependencies

import Utilities.Utilities as Utilities

import os

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

Utilities.SetTitle('Load Dependencies')

def cmd(command, show = False, workingDirectory = False):

	if (not workingDirectory):
		workingDirectory = Utilities.Settings.SolutionPath
	
	os.chdir(workingDirectory)
	ret = os.popen(command).read()

	if (show):
		print(ret)
	return ret

# Check is programs exists
try:
	cmd('npm --version')
except:
	print('npm dos not exists!')
	Utilities.ExitAction()

Utilities.SetTitle('Load Dependencies')

rootFolder = Utilities.Settings.SolutionPath

# Install NewWorldVSCodePlugin
print('Install NewWorldVSCodePlugin Dependencies')
folder = Utilities.GetSubPath('DevOps\\IDEPlugin\\NewWorldVSCodePlugin');

cmd(f'rd /s /q node_modules', False, folder)

cmd(f'npm install', True, folder)

print('Install NewWorldVSCodePlugin')
cmd(f'code --install-extension newworld-0.0.1.vsix', True, folder)

Utilities.SetTitle('Load Dependencies')

# git submodules
print('Delete "Dependencies"')

cmd(f'rd /s /q Dependencies')

print('Load Submodules')
cmd(f'echo %cd%&git submodule init', True)
cmd(f'echo %cd%&git submodule update', True)

cmd(f'md "Dependencies\\bin"')

# Premake
print(f'Create Premake')

cmd(f'start /MIN /WAIT cmd /c ".\\Bootstrap.bat&exit"', True, f"{rootFolder}\\Dependencies\\Premake")
cmd(f'copy /y "Dependencies\\Premake\\bin\\release\\premake5.exe" "Dependencies\\bin\\premake5.exe"', True)

Utilities.PresToConinue()