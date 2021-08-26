# LoadDependencies - Load the basic solution dependencies

import Utilities.Utilities as Utilities
import Utilities.MSBuild as MSBuild
import Utilities.VSIXBuilder as VSIXBuilder

# Utilities Functions
def CallNPM(command, show = False, workingDirectory = False):
	Utilities.CMD(command, show, workingDirectory)
	Utilities.SetTitle('Load Dependencies')

Utilities.SetTitle('Load Dependencies')

# Check if npm exists
try:
	CallNPM('npm --version')
except:
	print('npm dos not exists!')
	Utilities.ExitAction()

rootFolder = Utilities.Settings.SolutionPath

# Install NewWorldVSCodeExtension
print('Install NewWorldVSCodeExtension Dependencies')

jsonPath = Utilities.GetSubPath('DevOps\\IDEPlugin\\NewWorldVSCodeExtension\\package.json')
newWorldVSCodeExtensionVersion = Utilities.LoadJsonFile(jsonPath).version

folder = Utilities.GetSubPath('DevOps\\IDEPlugin\\NewWorldVSCodeExtension')

Utilities.CMD(f'rd /s /q node_modules', False, folder)

CallNPM(f'npm install', True, folder)

print('Install NewWorldVSCodeExtension')
Utilities.CMD(f'code --install-extension newworld-{newWorldVSCodeExtensionVersion}.vsix', True, folder)

# Install NewWorldPlugin
print('Install NewWorldPlugin')

MSBuild.Rebuild(Utilities.GetSubPath('DevOps\\IDEPlugin\\NewWorldPlugin\\NewWorldPlugin.sln'), 'Release')
newWorldPlugin = Utilities.GetSubPath('DevOps\\IDEPlugin\\NewWorldPlugin\\bin\\Release')

Utilities.CMD(f'NewWorldPlugin --install-extension', True, newWorldPlugin)

# Install NewWorldVisualStudioExtension
print('Install NewWorldVisualStudioExtension')

version = '0.0.2'

vsixPath = Utilities.GetSubPath(f'DevOps\\IDEPlugin\\NewWorldVisualStudioExtension\\NewWorld-{version}.vsix');

VSIXBuilder.Install(f'{vsixPath}', True)

# Install OtherExtensions
print('Install Todo List Extension')
vsixPath = Utilities.GetSubPath(f'DevOps\\IDEPlugin\\OtherExtensions\\TodoList\\saber2pr.todolist-0.1.6.vsix');

VSIXBuilder.Install(f'{vsixPath}', True)

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