# LoadDependencies - Load the basic solution dependencies

import Utilities.Utilities as Utilities
import Utilities.MSBuild as MSBuild

Utilities.SetTitle('Load Dependencies')

# Check is programs exists
try:
	Utilities.CMD('npm --version')
except:
	print('npm dos not exists!')
	Utilities.ExitAction()

Utilities.SetTitle('Load Dependencies')

rootFolder = Utilities.Settings.SolutionPath

# Install NewWorldVSCodePlugin
print('Install NewWorldVSCodePlugin Dependencies')

jsonPath = Utilities.GetSubPath('DevOps\\IDEPlugin\\NewWorldVSCodePlugin\\package.json')
newWorldVSCodePluginVersion = Utilities.LoadJsonFile(jsonPath).version

folder = Utilities.GetSubPath('DevOps\\IDEPlugin\\NewWorldVSCodePlugin')

Utilities.CMD(f'rd /s /q node_modules', False, folder)

Utilities.CMD(f'npm install', True, folder)

print('Install NewWorldVSCodePlugin')
Utilities.CMD(f'code --install-extension newworld-{newWorldVSCodePluginVersion}.vsix', True, folder)

# Install NewWorldWindowsPlugin
Utilities.SetTitle('Install NewWorldWindowsPlugin')

MSBuild.Build(Utilities.GetSubPath('DevOps\\IDEPlugin\\NewWorldWindowsPlugin\\NewWorldWindowsPlugin.sln'), "Release")
newWorldWindowsPlugin = Utilities.GetSubPath('DevOps\\IDEPlugin\\NewWorldWindowsPlugin\\bin\\Release')

Utilities.CMD(f'NewWorldPlugin --init-plugin', True, newWorldWindowsPlugin)

# Install NewWorldVisualStudioPlugin
Utilities.SetTitle('Install NewWorldVisualStudioPlugin')

MSBuild.Build(Utilities.GetSubPath('DevOps\\IDEPlugin\\NewWorldVisualStudioPlugin\\NewWorldVisualStudioPlugin.sln'), "Release")
newWorldVisualStudioPlugin = Utilities.GetSubPath('DevOps\\IDEPlugin\\NewWorldVisualStudioPlugin\\bin\\Release')

VSIXInstallerPath = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\VSIXInstaller";
Utilities.CMD(f'{VSIXInstallerPath} /quiet NewWorldVisualStudioPlugin.vsix', True, newWorldVisualStudioPlugin)

# git submodules
print('Delete "Dependencies"')

Utilities.CMD(f'rd /s /q Dependencies')

print('Load Submodules')
Utilities.CMD(f'git submodule init', True)
Utilities.CMD(f'git submodule update', True)

Utilities.CMD(f'md "Dependencies\\bin"')

# Premake
print(f'Create Premake')

Utilities.CMD(f'start /MIN /WAIT cmd /c ".\\Bootstrap.bat&exit"', True, f"{rootFolder}\\Dependencies\\Premake")
Utilities.CMD(f'copy /y "Dependencies\\Premake\\bin\\release\\premake5.exe" "Dependencies\\bin\\premake5.exe"', True)

Utilities.PresToConinue()