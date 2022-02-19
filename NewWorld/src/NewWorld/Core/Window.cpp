#include "nwpch.h"
#include "Window.h"

#include "NewWorld/Input/Key.h"
#include "NewWorld/Editor/EditorWindow.h"

#include "TempPanel.h"

#include <GLFW/glfw3.h>

namespace NewWorld::Core
{
	// Utilities
	static Input::Key ConvertMouseButtonKeyToKey(int key)
	{
		NW_ASSERT(key < 8, "Is not Mouse Button!");
		return (Input::Key)(key + 1);
	}

	static Input::Key ConvertKeybordKeyToKey(int key)
	{
		switch (key)
		{
		case GLFW_KEY_ENTER:
			return Input::Key::Enter;
		case GLFW_KEY_SPACE:
			return Input::Key::Space;
		case GLFW_KEY_ESCAPE:
			return Input::Key::Escape;

		case GLFW_KEY_UP:
			return Input::Key::UpArrow;
		case GLFW_KEY_DOWN:
			return Input::Key::DownArrow;
		case GLFW_KEY_LEFT:
			return Input::Key::LeftArrow;
		case GLFW_KEY_RIGHT:
			return Input::Key::RightArrow;
		}

		return Input::Key::UnSupported;
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

			// NW_INFO(NW_LOGGER_CORE ,"Window {} event Close", window.GetID());
			
			window.Close();
		});

		glfwSetWindowSizeCallback(m_WinHandle, [](GLFWwindow* winHandle, int width, int height) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			// NW_INFO(NW_LOGGER_CORE, "Window {} event SizeChanged ({}, {})", window.GetID(), width, height);
		});

		glfwSetKeyCallback(m_WinHandle, [](GLFWwindow* winHandle, int key, int scancode, int action, int mods) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			switch (action)
			{
				case GLFW_PRESS:
				{
					window.KeyPressed(ConvertKeybordKeyToKey(key));

					// NW_INFO(NW_LOGGER_CORE, "Window {} event KeyPressed {}, {}, {}, {}", window.GetID(), key, scancode, mods, false);
					break;
				}
				case GLFW_REPEAT:
				{
					window.KeyPressed(ConvertKeybordKeyToKey(key));

					// NW_INFO(NW_LOGGER_CORE, "Window {} event KeyPressed {}, {}, {}, {}", window.GetID(), key, scancode, mods, true);
					break;
				}
				case GLFW_RELEASE:
				{
					// TEMP: for testing
					//
					if (key == GLFW_KEY_SPACE)
					{
						double xPos;
						double yPos;

						glfwGetCursorPos(winHandle, &xPos, &yPos);
						SharedPointer<Temp::TempPanel> newPanel(xPos, yPos);

						window.GetMainPanel().AddComponent(newPanel);
					}
					//

					window.KeyReleased(ConvertKeybordKeyToKey(key));

					// NW_INFO(NW_LOGGER_CORE, "Window {} event KeyReleased {}, {}, {}", window.GetID(), key, scancode, mods);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_WinHandle, [](GLFWwindow* winHandle, int key, int action, int mods) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			double xPos;
			double yPos;

			glfwGetCursorPos(winHandle, &xPos, &yPos);

			switch (action)
			{
				case GLFW_PRESS:
				{
					window.MouseKeyPressed(ConvertMouseButtonKeyToKey(key), xPos, yPos);

					// NW_INFO(NW_LOGGER_CORE, "Window {} event MouseButtonPressed {}, {}, {}, ({}, {})", window.GetID(), key, mods, false, xPos, yPos);
					break;
				}
				case GLFW_REPEAT:
				{
					window.MouseKeyPressed(ConvertMouseButtonKeyToKey(key), xPos, yPos);

					// NW_INFO(NW_LOGGER_CORE, "Window {} event MouseButtonPressed {}, {}, {}, ({}, {})", window.GetID(), key, mods, true, xPos, yPos);
					break;
				}
				case GLFW_RELEASE:
				{
					window.MouseKeyReleased(ConvertMouseButtonKeyToKey(key), xPos, yPos);

					// NW_INFO(NW_LOGGER_CORE, "Window {} event MouseButtonReleased {}, {}, ({}, {})", window.GetID(), key, mods, xPos, yPos);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(m_WinHandle, [](GLFWwindow* winHandle, double xPos, double yPos) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			window.MouseHover(xPos, yPos);

			// NW_INFO(NW_LOGGER_CORE, "Window {} event MouseMoved ({}, {})", window.GetID(), xPos, yPos);
		});

		glfwSetScrollCallback(m_WinHandle, [](GLFWwindow* winHandle, double xOffset, double yOffset) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			window.MouseScrolled(yOffset);

			// NW_INFO(NW_LOGGER_CORE, "Window {} event MouseScrolled ({}, {})", window.GetID(), xOffset, yOffset);
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
		m_ShouldToClose = true;
	}

	bool Window::CloseIfNeed()
	{
		if (m_ShouldToClose)
		{
			glfwDestroyWindow(m_WinHandle);
			m_WinHandle = nullptr;

			NW_INFO(NW_LOGGER_CORE, "The window \"{}\" Clossed", m_Title);
		}

		return m_ShouldToClose;
	}

	void Window::HandleEvents()
	{
		glfwSwapBuffers(m_WinHandle);
		glfwPollEvents();
	}

	// Events
	void Window::Update()
	{
		glfwMakeContextCurrent(m_WinHandle);
	}
}