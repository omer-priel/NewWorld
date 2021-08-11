# GenerateProjects - Generate IDE Projects

import Scripts.Utilities as Utilities

import os

Utilities.SetTitle("Generate Projects")

command = Utilities.Settings['SolutionPath'] + '\\Dependencies\\bin\\premake5.exe vs2019 --file=Solution.build.lua'
os.system(command)

Utilities.PresToConinue()