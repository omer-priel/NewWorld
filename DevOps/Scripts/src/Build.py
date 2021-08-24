# Build - Build all the applications

import Utilities.Utilities as Utilities
import Utilities.MSBuild as MSBuild

Utilities.SetTitle("Build")

jsonPath = Utilities.GetSubPath('DevOps\\IDEPlugin\\NewWorldVSCodePlugin\\package.json')
newWorldSettings = Utilities.LoadJsonFile(Utilities.GetSubPath('NewWorld.nwe'))

# build New World Engine
projectFilePath = Utilities.GetSubPath('NewWorld\\NewWorld.vcxproj')
MSBuild.Clean(projectFilePath, 'Release')
MSBuild.Build(projectFilePath, 'Release')

# build projects
for project in newWorldSettings.projects:
    if ((build in project) and project.build):
        projectFilePath = Utilities.GetSubPath(project.folder) + f'\\{project.name}.vcxproj';
        MSBuild.Clean(projectFilePath, 'Release')
        MSBuild.Build(projectFilePath, 'Release')

Utilities.PresToConinue()