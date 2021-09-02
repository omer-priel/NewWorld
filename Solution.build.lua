workspace "NewWorld"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
--	include "Dependencies/GLFW"
--	include "Dependencies/imgui"
group ""

project "NewWorld"
	location "NewWorld"
	icon "Logo.ico"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

	pchheader "nwpch.h"
	pchsource "NewWorld/src/nwpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src"
	}

	links 
	{ 
--		"GLFW",
--		"ImGui",
		"opengl32.lib"
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
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"NewWorld/src"
	}

	links
	{
		"NewWorld"
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
