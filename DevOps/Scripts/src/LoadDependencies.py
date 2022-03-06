# LoadDependencies - Load the basic solution dependencies

import Utilities.Utilities as Utilities
import Utilities.MSBuild as MSBuild
import Utilities.VSIXBuilder as VSIXBuilder

# "Progress Bar"
lsatStage = 9

debugMode = False
stage = 0
def StartStage(title):
	global stage
	stage = stage + 1
	Utilities.SetTitle(f'Load Dependencies [{stage}\\{lsatStage}]')
	print(title)
	if (debugMode):
		print(f'------------{stage}------------')
		input('')

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

# Install NewWorldPlugin
StartStage('Install NewWorldPlugin')

MSBuild.Rebuild(Utilities.GetSubPath('DevOps\\NewWorldPlugin\\NewWorldPlugin.sln'), 'Release')
newWorldPlugin = Utilities.GetSubPath('DevOps\\NewWorldPlugin\\bin\\Release')

Utilities.CMD(f'NewWorldPlugin install-extension', True, newWorldPlugin)

# Install NewWorldVisualStudioExtension
StartStage('Install NewWorldVisualStudioExtension')

version = '0.0.4'

vsixPath = Utilities.GetSubPath(f'DevOps\\IDEExtension\\NewWorldVisualStudioExtension\\NewWorld-{version}.vsix');

VSIXBuilder.Install(vsixPath)

# Install NewWorldVSCodeExtension
StartStage('Build NewWorldVSCodeExtension')

jsonPath = Utilities.GetSubPath('DevOps\\IDEExtension\\NewWorldVSCodeExtension\\package.json')

folder = Utilities.GetSubPath('DevOps\\IDEExtension\\NewWorldVSCodeExtension')

Utilities.CMD(f'rd /s /q node_modules', False, folder)

CallNPM(f'npm install', True, folder)
CallNPM(f'npm run scripts:package', True, folder)

StartStage('Install NewWorldVSCodeExtension')
Utilities.CMD(f'code --install-extension newworld.vsix', True, folder)

# Install OtherExtensions
StartStage('Install Todo List Extension')
vsixPath = Utilities.GetSubPath(f'DevOps\\IDEExtension\\OtherExtensions\\TodoList\\saber2pr.todolist-0.1.6.vsix');

VSIXBuilder.Install(vsixPath)

# git submodules
StartStage('Delete "Dependencies"')

Utilities.CMD(f'rd /s /q Dependencies')

Utilities.CMD(f'xcopy /Q /E /Y /I DevOps\RawDependencies\GLAD Dependencies\GLAD')
Utilities.CMD(f'xcopy /Q /E /Y /I DevOps\RawDependencies\GLAD_Debug Dependencies\GLAD_Debug')

StartStage('Load Submodules')
Utilities.CMD(f'git submodule init', True)
Utilities.CMD(f'git submodule update', True)

Utilities.CMD(f'md "Dependencies\\bin"')

# Premake
StartStage(f'Create the Premake Tool')

Utilities.CMD(f'start /MIN /WAIT cmd /c ".\\Bootstrap.bat&exit"', True, Utilities.GetSubPath(f'\Dependencies\\Premake'))
Utilities.CMD(f'copy /y "Dependencies\\Premake\\bin\\release\\premake5.exe" "Dependencies\\bin\\premake5.exe"', True)

# Generate Projects
StartStage(f'Generate Projects')

Utilities.CMD(f'NewWorldPlugin generate-projects')

Utilities.PresToConinue()