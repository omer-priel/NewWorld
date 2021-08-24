# MSBuild - class that

import Utilities.Utilities as Utilities

# load MSBuild folder
MSBuildFolder = r'C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin'
MSBuildPath = '"' + MSBuildFolder + r'\MSBuild.exe' + '"'

# Rebuild Solution or project
def Rebuild(projectPath, configurationName):
    Utilities.CMD(f'{MSBuildPath} {projectPath} -t:Rebuild -p:Configuration={configurationName}', True)

# Build Solution or project
def Clean(projectPath, configurationName):
    Utilities.CMD(f'{MSBuildPath} {projectPath} -t:Clean -p:Configuration={configurationName}', True)

# Build Solution or project
def Build(projectPath, configurationName):
    Utilities.CMD(f'{MSBuildPath} {projectPath} -t:Build -p:Configuration={configurationName}', True)

# Run Solution target or project target
def Run(projectPath, configurationName):
    Utilities.CMD(f'{MSBuildPath} {projectPath} -t:Run -p:Configuration={configurationName}', True)