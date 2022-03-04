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

project "NewWorld"
	location "NewWorld"
	icon "Logo.ico"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
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
        "%{DependenciesDir}/GLM",
        "%{DependenciesDir}/GLFW/include"
	}

	links 
	{ 
        "opengl32.lib",
        "GLFW"
--		"ImGui",
	}

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
	cppdialect "C++20"
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
        "Sandbox/src",
        "%{DependenciesDir}/GLM"
	}

	links
	{
		"NewWorld"
	}

    postbuildcommands
    {
        "{COPYDIR} %{wks.location}/Assets %{cfg.targetdir}/assets"
    }

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
