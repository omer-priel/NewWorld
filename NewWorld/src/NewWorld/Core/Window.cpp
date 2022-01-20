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
					window.GetMainPanel().RemoveComponent((key == GLFW_KEY_SPACE) ? window.GetMainPanel().GetComponents().size() - 1 : 0);

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
					SharedPointer<Editor::UI::Panel> newPanel(xPos - 20, yPos - 20, 40, 40
						, (key == GLFW_MOUSE_BUTTON_LEFT) ? Graphics::Colors::Red : Graphics::Colors::Blue);

					window.GetMainPanel().AddComponent((SharedPointer<Editor::Component>)newPanel);

					SharedPointer<Editor::UI::Panel> parent = newPanel;

					for (size_t i = 18; i > 2; i -= 2)
					{
						SharedPointer<Editor::UI::Panel> childPanel(xPos - i, yPos - i, i*2, i*2
							, ((i / 2) % 2 == 0) ? Graphics::Colors::Blue : Graphics::Colors::Red);

						parent->AddComponent(childPanel);
						childPanel = parent;
					}

					NW_INFO(NW_LOGGER_CORE, "Window {} event MouseButtonReleased {}, {}, ({}, {})", window.GetID(), key, mods, xPos, yPos);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_WinHandle, [](GLFWwindow* winHandle, double xOffset, double yOffset) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			for (auto& comp : window.GetMainPanel().GetComponents())
			{
				SharedPointer<Editor::UI::Panel> panel = comp;
				
				panel->SetX(panel->GetX() - yOffset * 5);
				panel->SetY(panel->GetY() - yOffset * 5);
				panel->SetWidth(panel->GetWidth() + yOffset * 10);
				panel->SetHeight(panel->GetHeight() + yOffset * 10);
			}

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