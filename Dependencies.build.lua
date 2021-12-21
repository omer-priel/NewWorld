DependenciesDir = "Dependencies"

--include "%{DependenciesDir}/GLFW"
--include "%{DependenciesDir}/ImGui"

project "GLM"
	location "%{DependenciesDir}/Workspace"
	icon "Logo.ico"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	files
	{
        "%{DependenciesDir}/GLM/glm/**.hpp",
        "%{DependenciesDir}/GLM/glm/**.inl",
	}