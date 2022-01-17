DependenciesDir = "Dependencies"

--include "%{DependenciesDir}/ImGui"

project "GLM"
	location "%{DependenciesDir}/Workspace"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	files
	{
        "%{DependenciesDir}/GLM/glm/**.hpp",
        "%{DependenciesDir}/GLM/glm/**.inl",
	}

project "GLFW"
    location "%{DependenciesDir}/Workspace"
    kind "StaticLib"
    language "C"
    systemversion "latest"
    staticruntime "On"

	files
	{
        "%{DependenciesDir}/GLFW/include/GLFW/glfw3.h",
        "%{DependenciesDir}/GLFW/include/GLFW/glfw3native.h",
        "%{DependenciesDir}/GLFW/src/glfw_config.h",
        "%{DependenciesDir}/GLFW/src/context.c",
        "%{DependenciesDir}/GLFW/src/init.c",
        "%{DependenciesDir}/GLFW/src/input.c",
        "%{DependenciesDir}/GLFW/src/monitor.c",
        "%{DependenciesDir}/GLFW/src/vulkan.c",
        "%{DependenciesDir}/GLFW/src/window.c"
    }
    
	filter "system:windows"
        buildoptions { "-std=c11", "-lgdi32" }
        
        files
        {
            "%{DependenciesDir}/GLFW/src/win32_init.c",
            "%{DependenciesDir}/GLFW/src/win32_joystick.c",
            "%{DependenciesDir}/GLFW/src/win32_monitor.c",
            "%{DependenciesDir}/GLFW/src/win32_time.c",
            "%{DependenciesDir}/GLFW/src/win32_thread.c",
            "%{DependenciesDir}/GLFW/src/win32_window.c",
            "%{DependenciesDir}/GLFW/src/wgl_context.c",
            "%{DependenciesDir}/GLFW/src/egl_context.c",
            "%{DependenciesDir}/GLFW/src/osmesa_context.c"
        }

		defines 
		{ 
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
		}
        
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
