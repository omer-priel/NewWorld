#include "nwpch.h"
#include "Window.h"

#include "NewWorld/Editor/EditorWindow.h"

#include <GLFW/glfw3.h>

namespace NewWorld::Core
{
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

			NW_INFO(NW_LOGGER_CORE ,"Window {} event Close", window.GetID());
		});

		glfwSetWindowSizeCallback(m_WinHandle, [](GLFWwindow* winHandle, int width, int height) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			NW_INFO(NW_LOGGER_CORE, "Window {} event SizeChanged ({}, {})", width, height);
		});

		glfwSetKeyCallback(m_WinHandle, [](GLFWwindow* winHandle, int key, int scancode, int action, int mods) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			switch (action)
			{
				case GLFW_PRESS:
				{
					NW_INFO(NW_LOGGER_CORE, "Window {} event KeyPressed {}, {}, {}, {}", window.GetID(), key, scancode, mods, false);
					break;
				}
				case GLFW_REPEAT:
				{
					NW_INFO(NW_LOGGER_CORE, "Window {} event KeyPressed {}, {}, {}, {}", window.GetID(), key, scancode, mods, true);
					break;
				}
				case GLFW_RELEASE:
				{
					NW_INFO(NW_LOGGER_CORE, "Window {} event KeyReleased {}, {}, {}", window.GetID(), key, scancode, mods);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_WinHandle, [](GLFWwindow* winHandle, int key, int action, int mods) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			switch (action)
			{
				case GLFW_PRESS:
				{
					NW_INFO(NW_LOGGER_CORE, "Window {} event MouseButtonPressed {}, {}, {}", window.GetID(), key, mods, false);
					break;
				}
				case GLFW_REPEAT:
				{
					NW_INFO(NW_LOGGER_CORE, "Window {} event MouseButtonPressed {}, {}, {}", window.GetID(), key, mods, true);
					break;
				}
				case GLFW_RELEASE:
				{
					SharedPointer<Editor::UI::Panel> newPanel(100, 100, 100, 100, Graphics::Colors::Red);
					SharedPointer<Editor::Component> newComp = newPanel;

					//window.GetMainPanel().AddComponent(newComp);

					NW_INFO(NW_LOGGER_CORE, "Window {} event MouseButtonReleased {}, {}", window.GetID(), key, mods);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_WinHandle, [](GLFWwindow* winHandle, double xOffset, double yOffset) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			Graphics::Color color = window.GetMainPanel().GetBackgroundColor();
			color.b += yOffset * 0.03f;
			window.GetMainPanel().SetBackgroundColor(color);

			NW_INFO(NW_LOGGER_CORE, "Window {} event MouseScrolled ({}, {})", window.GetID(), xOffset, yOffset);
		});

		glfwSetCursorPosCallback(m_WinHandle, [](GLFWwindow* winHandle, double xPos, double yPos) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			Graphics::Color color = window.GetMainPanel().GetBackgroundColor();
			color.r = xPos / window.GetWidth();
			color.g = yPos / window.GetHeight();
			window.GetMainPanel().SetBackgroundColor(color);

			NW_INFO(NW_LOGGER_CORE, "Window {} event MouseMoved ({}, {})", window.GetID(), xPos, yPos);
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
		glfwMakeContextCurrent(m_WinHandle);
	}
}