#include "nwpch.h"
#include "Window.h"

#include <GLFW/glfw3.h>

namespace NewWorld::Core
{
	// Static
	void Window::Initialize()
	{
		GraphicsAPI::GraphicsAPI::Initialize();
	}

	// None-Static
	// Init
	void Window::Init()
	{
		m_WinHandle = glfwCreateWindow((int)m_Width, (int)m_Height, m_Title.GetPointer(), nullptr, nullptr);
		glfwMakeContextCurrent(m_WinHandle);
		glfwSetWindowUserPointer(m_WinHandle, this);
		glfwSwapInterval(1); // Set VSync true

		// Register Window Events
		Window::InitEvents();

		NW_INFO(NW_LOGGER_CORE, "Window Created \"{}\" ({}, {}) ", m_Title, m_Width, m_Height);
	}

	void Window::InitEvents()
	{
		// Set GLFW callbacks
		glfwSetWindowCloseCallback(m_WinHandle, [](GLFWwindow* window) {
			NW_INFO(NW_LOGGER_CORE ,"Event Close");
		});

		glfwSetWindowSizeCallback(m_WinHandle, [](GLFWwindow* window, int width, int height) {
			NW_INFO(NW_LOGGER_CORE, "Event SizeChanged ({}, {})", width, height);
		});

		glfwSetKeyCallback(m_WinHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			switch (action)
			{
				case GLFW_PRESS:
				{
					NW_INFO(NW_LOGGER_CORE, "Event KeyPressed {}, {}, {}, {}", key, scancode, mods, false);
					break;
				}
				case GLFW_REPEAT:
				{
					NW_INFO(NW_LOGGER_CORE, "Event KeyPressed {}, {}, {}, {}", key, scancode, mods, true);
					break;
				}
				case GLFW_RELEASE:
				{
					NW_INFO(NW_LOGGER_CORE, "Event KeyPressed {}, {}, {}", key, scancode, mods);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_WinHandle, [](GLFWwindow* window, int key, int action, int mods) {
			switch (action)
			{
				case GLFW_PRESS:
				{
					NW_INFO(NW_LOGGER_CORE, "Event MouseButtonPressed {}, {}, {}", key, mods, false);
					break;
				}
				case GLFW_REPEAT:
				{
					NW_INFO(NW_LOGGER_CORE, "Event MouseButtonPressed {}, {}, {}", key, mods, true);
					break;
				}
				case GLFW_RELEASE:
				{
					NW_INFO(NW_LOGGER_CORE, "Event MouseButtonPressed {}, {}", key, mods);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_WinHandle, [](GLFWwindow* window, double xOffset, double yOffset) {
			NW_INFO(NW_LOGGER_CORE, "Event MouseScrolled ({}, {})", xOffset, yOffset);
		});

		glfwSetCursorPosCallback(m_WinHandle, [](GLFWwindow* window, double xPos, double yPos) {
			NW_INFO(NW_LOGGER_CORE, "Event MouseMoved ({}, {})", xPos, yPos);
		});
	}

	// Getters
	bool Window::IsVisible() const
	{
		return glfwGetWindowAttrib(m_WinHandle, GLFW_VISIBLE) == 1;
	}

	// Actions
	void Window::Show()
	{
		glfwShowWindow(m_WinHandle);
	}

	void Window::Hide()
	{
		glfwHideWindow(m_WinHandle);
	}

	void Window::Close()
	{
		if (IsAlive())
		{
			NW_INFO(NW_LOGGER_CORE, "Window Clossing \"{}\" ", m_Title);

			glfwDestroyWindow(m_WinHandle);
			m_WinHandle = nullptr;
		}
	}

	void Window::HandleEvents()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_WinHandle);
	}

	// Events
    
}