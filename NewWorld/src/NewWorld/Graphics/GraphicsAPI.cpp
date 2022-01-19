#include "nwpch.h"
#include "GraphicsAPI.h"

#include <GLFW/glfw3.h>

namespace NewWorld::Graphics
{
	void GraphicsAPI::Initialize()
	{
		int success = glfwInit();
		NW_ASSERT(success, "Could not intialize GLFW!");
	}

	void GraphicsAPI::Finalize()
	{
		glfwTerminate();
	}
}