#include "nwpch.h"
#include "GraphicsAPI.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace NewWorld::Graphics
{
	void error_callback(int error, const char* description)
	{
		NW_ERROR(NW_LOGGER_CORE, "{}", description);
	}

	void GraphicsAPI::Initialize()
	{
		int success;

		success = glfwInit();
		NW_ASSERT(success, "Could not intialize GLFW!");

		success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NW_ASSERT(success, "Could not intialize GLAD!");

		glfwSetErrorCallback(error_callback);
	}

	void GraphicsAPI::Finalize()
	{
		glfwTerminate();
	}
}