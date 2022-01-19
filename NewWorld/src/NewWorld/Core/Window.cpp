#include "nwpch.h"
#include "Window.h"

#include "NewWorld/Editor/EditorWindow.h"

#include <GLFW/glfw3.h>

namespace NewWorld::Core
{
	// Static
	void Window::Initialize()
	{
		GraphicsAPI::GraphicsAPI::Initialize();
	}


	void Window::Finalize()
	{
		GraphicsAPI::GraphicsAPI::Finalize();
	}

	// None-Static
	// Init
	void Window::Create()
	{
		m_WinHandle = glfwCreateWindow((int)m_Width, (int)m_Height, m_Title.GetPointer(), nullptr, nullptr);
		glfwMakeContextCurrent(m_WinHandle);
		glfwSetWindowUserPointer(m_WinHandle, this);
		glfwSwapInterval(1); // Set VSync true

		// Register Window Events
		Window::ReggisterEvents();

		NW_INFO(NW_LOGGER_CORE, "Window Created \"{}\" ({}, {}) ", m_Title, m_Width, m_Height);
	}

	void Window::ReggisterEvents()
	{
		// Set GLFW callbacks
		glfwSetWindowCloseCallback(m_WinHandle, [](GLFWwindow* winHandle) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			NW_DEBUG(NW_LOGGER_CORE, window.GetMainPanel().GetBackgroundColor());

			NW_INFO(NW_LOGGER_CORE ,"Event Close");
		});

		glfwSetWindowSizeCallback(m_WinHandle, [](GLFWwindow* winHandle, int width, int height) {
			Window& window = *(Window*)glfwGetWindowUserPointer(winHandle);

			NW_INFO(NW_LOGGER_CORE, "Event SizeChanged ({}, {})", width, height);
		});

		glfwSetKeyCallback(m_WinHandle, [](GLFWwindow* winHandle, int key, int scancode, int action, int mods) {
			Window& window = *(Window*)glfwGetWindowUserPointer(winHandle);

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
					NW_INFO(NW_LOGGER_CORE, "Event KeyReleased {}, {}, {}", key, scancode, mods);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_WinHandle, [](GLFWwindow* winHandle, int key, int action, int mods) {
			Window& window = *(Window*)glfwGetWindowUserPointer(winHandle);

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
					NW_INFO(NW_LOGGER_CORE, "Event MouseButtonReleased {}, {}", key, mods);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_WinHandle, [](GLFWwindow* winHandle, double xOffset, double yOffset) {
			Window& window = *(Window*)glfwGetWindowUserPointer(winHandle);

			NW_INFO(NW_LOGGER_CORE, "Event MouseScrolled ({}, {})", xOffset, yOffset);
		});

		glfwSetCursorPosCallback(m_WinHandle, [](GLFWwindow* winHandle, double xPos, double yPos) {
			Window& window = *(Window*)glfwGetWindowUserPointer(winHandle);

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
	void Window::Update()
	{

	}
}