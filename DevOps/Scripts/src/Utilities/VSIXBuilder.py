# VSIXBuilder - Class for build and install .vsix files
# 				Use VSIXInstaller.exe

import Utilities.Utilities as Utilities

# Members
VSIXInstallerFolder = r'C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE'
VSIXInstaller = '"' + VSIXInstallerFolder + r'\VSIXInstaller.exe' + '"'

# Rebuild Solution or project
def Install(filepath):
    Utilities.CMD(f'{VSIXInstallerFolder} /quiet \"{filepath}\"', True)

def Uninstall(id):
	Utilities.CMD(f'{VSIXInstallerFolder} /quiet /uninstall:{id}', True)