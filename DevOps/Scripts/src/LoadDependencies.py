# LoadDependencies - Load the basic solution dependencies

import Utilities.Utilities as Utilities
import Utilities.MSBuild as MSBuild

Utilities.SetTitle('Load Dependencies')

# Check if npm exists
try:
	Utilities.CMD('npm --version')
except:
	print('npm dos not exists!')
	Utilities.ExitAction()

Utilities.SetTitle('Load Dependencies')

rootFolder = Utilities.Settings.SolutionPath

# Install NewWorldVSCodeExtension
print('Install NewWorldVSCodeExtension Dependencies')

jsonPath = Utilities.GetSubPath('DevOps\\IDEPlugin\\NewWorldVSCodePlugin\\package.json')
newWorldVSCodeExtensionVersion = Utilities.LoadJsonFile(jsonPath).version

folder = Utilities.GetSubPath('DevOps\\IDEPlugin\\NewWorldVSCodePlugin')

Utilities.CMD(f'rd /s /q node_modules', False, folder)

Utilities.CMD(f'npm install', True, folder)

print('Install NewWorldVSCodeExtension')
Utilities.CMD(f'code --install-extension newworld-{newWorldVSCodeExtensionVersion}.vsix', True, folder)

# Install NewWorldWindowsExtension
print('Install NewWorldWindowsExtension')

MSBuild.Rebuild(Utilities.GetSubPath('DevOps\\IDEPlugin\\NewWorldWindowsPlugin\\NewWorldWindowsPlugin.sln'), 'Release')
newWorldWindowsExtension = Utilities.GetSubPath('DevOps\\IDEPlugin\\NewWorldWindowsPlugin\\bin\\Release')

Utilities.CMD(f'NewWorldPlugin --install-extension', True, newWorldWindowsExtension)

# Install NewWorldVisualStudioExtension
print('Install NewWorldVisualStudioExtension')

version = '0.0.2'

VSIXInstallerPath = '"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\Common7\\IDE\\VSIXInstaller.exe"'
vsixPath = Utilities.GetSubPath(f'DevOps\\IDEPlugin\\NewWorldVisualStudioPlugin\\NewWorld-{version}.vsix');

Utilities.CMD(f'{VSIXInstallerPath} /quiet "{vsixPath}"', True)

# git submodules
print('Delete "Dependencies"')

Utilities.CMD(f'rd /s /q Dependencies')

print('Load Submodules')
Utilities.CMD(f'git submodule init', True)
Utilities.CMD(f'git submodule update', True)

Utilities.CMD(f'md "Dependencies\\bin"')

# Premake
print(f'Create the Premake Tool')

Utilities.CMD(f'start /MIN /WAIT cmd /c ".\\Bootstrap.bat&exit"', True, f"{rootFolder}\\Dependencies\\Premake")
Utilities.CMD(f'copy /y "Dependencies\\Premake\\bin\\release\\premake5.exe" "Dependencies\\bin\\premake5.exe"', True)

Utilities.PresToConinue()