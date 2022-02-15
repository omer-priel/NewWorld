#include "nwpch.h"
#include "Window.h"

#include "NewWorld/Input/Key.h"
#include "NewWorld/Editor/EditorWindow.h"

#include <GLFW/glfw3.h>

namespace NewWorld::Core
{
	// Utilities
	static Input::Key ConvertMouseButtonKeyToKey(int key)
	{
		return (Input::Key)(key % 8);
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

			NW_INFO(NW_LOGGER_CORE ,"Window {} event Close", window.GetID());
			
			window.Close();
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
					double xPos;
					double yPos;

					glfwGetCursorPos(winHandle, &xPos, &yPos);

					SharedPointer<Editor::UI::Panel> newPanel(xPos - 20, yPos - 20, 40, 40, Graphics::Colors::Magenta);

					newPanel->SetClickHandler([](Editor::Component& sender, const Editor::Events::ClickEvent& e) {
						Editor::UI::Panel& panel = (Editor::UI::Panel&)sender;
						NW_WARN(NW_LOGGER_CORE, "Click Key: {}, Pos: ({}, {})", (uint)e.GetKey(), e.GetX(), e.GetY());

						Graphics::Color color = panel.GetBackgroundColor();
						color.g += 0.5f;

						SharedPointer<Editor::UI::Panel> newSubPanel(e.GetX() - 5, e.GetY() - 5, 10, 10, color);

						panel.AddComponent(newSubPanel);
					});

					newPanel->SetCreateHandler([](Editor::Component& sender) {
						NW_WARN(NW_LOGGER_CORE, "Create");
					});

					newPanel->SetDestroyHandler([](Editor::Component& sender) {
						NW_WARN(NW_LOGGER_CORE, "Destroy");
					});

					window.GetMainPanel().AddComponent(newPanel);

					NW_INFO(NW_LOGGER_CORE, "Window {} event KeyReleased {}, {}, {}", window.GetID(), key, scancode, mods);
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
					NW_INFO(NW_LOGGER_CORE, "Window {} event MouseButtonPressed {}, {}, {}, ({}, {})", window.GetID(), key, mods, false, xPos, yPos);
					break;
				}
				case GLFW_REPEAT:
				{
					NW_INFO(NW_LOGGER_CORE, "Window {} event MouseButtonPressed {}, {}, {}, ({}, {})", window.GetID(), key, mods, true, xPos, yPos);
					break;
				}
				case GLFW_RELEASE:
				{
					window.Click(Editor::Events::ClickEvent(ConvertMouseButtonKeyToKey(key), xPos, yPos));

					NW_INFO(NW_LOGGER_CORE, "Window {} event MouseButtonReleased {}, {}, ({}, {})", window.GetID(), key, mods, xPos, yPos);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_WinHandle, [](GLFWwindow* winHandle, double xOffset, double yOffset) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			NW_INFO(NW_LOGGER_CORE, "Window {} event MouseScrolled ({}, {})", window.GetID(), xOffset, yOffset);
		});

		glfwSetCursorPosCallback(m_WinHandle, [](GLFWwindow* winHandle, double xPos, double yPos) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

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