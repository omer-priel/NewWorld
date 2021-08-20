import Utilities.Utilities as Utilities

MSBuildFolder = r'C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin'
MSBuildPath = '"' + MSBuildFolder + r'\MSBuild.exe' + '"'

def Build(projectPath, configurationName):
    Utilities.CMD(f'{MSBuildPath} {projectPath} -t:Rebuild -p:Configuration={configurationName}', True)