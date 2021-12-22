workspace "NewWorld"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
DependenciesDir = "Dependencies"

group "Dependencies"
    include "./Dependencies.build"
group ""

ProjectSettings = {}
ProjectSettings["LoggersCount"] = "2"

project "NewWorld"
	location "NewWorld"
	icon "Logo.ico"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("bin/int/" .. OutputDir .. "/%{prj.name}")

	pchheader "nwpch.h"
	pchsource "NewWorld/src/nwpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
        "%{DependenciesDir}/GLM"
	}

	links 
	{ 
--		"GLFW",
--		"ImGui",
		"opengl32.lib"
	}

    defines {"NW_SETTINGS_LOGGERS_COUNT=%{ProjectSettings.LoggersCount}" }

	filter "system:windows"
		defines "NW_PLATFORM_WINDOWS"
		systemversion "latest"

	filter "configurations:Debug"
		defines "NW_CONFIG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NW_CONFIG_RELEASE"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	icon "Logo.ico"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("bin/int/" .. OutputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"NewWorld/src",
        "%{DependenciesDir}/GLM"
	}

	links
	{
		"NewWorld"
	}

    defines {"NW_SETTINGS_LOGGERS_COUNT=%{ProjectSettings.LoggersCount}" }

	filter "system:windows"
		defines "NW_PLATFORM_WINDOWS"
		systemversion "latest"

	filter "configurations:Debug"
		defines "NW_CONFIG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NW_CONFIG_RELEASE"
		runtime "Release"
		optimize "on"
