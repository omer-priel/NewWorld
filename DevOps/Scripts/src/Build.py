# Build - Build all the applications

import Utilities.Utilities as Utilities
import Utilities.MSBuild as MSBuild

Utilities.SetTitle("Build")

# Build the Solution
projectFilePath = Utilities.GetSubPath('NewWorld.sln')
MSBuild.Clean(projectFilePath, 'Release')
MSBuild.Build(projectFilePath, 'Release')

Utilities.PresToConinue()