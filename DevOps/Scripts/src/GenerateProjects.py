# GenerateProjects - Generate IDE Projects

import Utilities.Utilities as Utilities

import os

Utilities.SetTitle("Generate Projects")

# Generate the projects by premake
premake_path = Utilities.GetSubPath("Dependencies\\bin\\premake5.exe")
build_config_path = Utilities.GetSubPath("Solution.build.lua")
command = f"{premake_path} vs2019 --file={build_config_path}"
os.system(command)

Utilities.PresToConinue()