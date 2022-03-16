#include "nwpch.h"
#include "Window.h"

#include "NewWorld/Input/Key.h"
#include "NewWorld/Editor/EditorWindow.h"

#include "NewWorld/Editor/UI/BordedLabel.h"
#include "NewWorld/Editor/UI/CheckBox.h"
#include "NewWorld/Editor/UI/ToggleButton.h"

#include <glad/glad.h>
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

		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NW_ASSERT(success, "Could not intialize GLAD!");

		// Register Window Events
		Window::ReggisterEvents();

		NW_INFO(NW_LOGGER_CORE, "Window Created \"{}\" ({}, {}) ", m_Title, m_Width, m_Height);
	}

	void Window::ReggisterEvents()
	{
		// Set GLFW callbacks
		glfwSetWindowCloseCallback(m_WinHandle, [](GLFWwindow* winHandle) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);
			
			window.Close();
		});

		glfwSetWindowSizeCallback(m_WinHandle, [](GLFWwindow* winHandle, int width, int height) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			// TODO: Support Size Changed
		});

		glfwSetKeyCallback(m_WinHandle, [](GLFWwindow* winHandle, int key, int scancode, int action, int mods) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			switch (action)
			{
				case GLFW_PRESS:
				{
					window.KeyPressed(ConvertKeybordKeyToKey(key));
					break;
				}
				case GLFW_REPEAT:
				{
					window.KeyPressed(ConvertKeybordKeyToKey(key));
					break;
				}
				case GLFW_RELEASE:
				{
					// TODO: remove
					// Testing unit
					if (key == GLFW_KEY_SPACE)
					{
						double xPos;
						double yPos;

						glfwGetCursorPos(winHandle, &xPos, &yPos);
						yPos = (double)window.GetHeight() - yPos;

						using namespace NewWorld::Editor::UI;

						// Create new UI Component					
						SharedPointer<CheckBox> checkBox1(xPos - 24, yPos - 24);
						SharedPointer<CheckBox> checkBox2(xPos + 10, yPos - 24, true);
						SharedPointer<CheckBox> checkBox3(xPos - 24, yPos + 10 , false, Graphics::Colors::LightBlue, Graphics::Colors::CobaltBlue);
						SharedPointer<CheckBox> checkBox4(xPos + 10, yPos + 10, true, Graphics::Colors::LightBlue, Graphics::Colors::CobaltBlue);

						window.GetMainPanel().AddComponent(checkBox1);
						window.GetMainPanel().AddComponent(checkBox2);
						window.GetMainPanel().AddComponent(checkBox3);
						window.GetMainPanel().AddComponent(checkBox4);

						SharedPointer<ToggleButton> toggleButton1(xPos + 100 - 24, yPos - 24);
						SharedPointer<ToggleButton> toggleButton2(xPos + 100 + 10, yPos - 24, true);
						SharedPointer<ToggleButton> toggleButton3(xPos + 100 - 24, yPos + 10, false, Graphics::Colors::LightBlue, Graphics::Colors::CobaltBlue);
						SharedPointer<ToggleButton> toggleButton4(xPos + 100 + 10, yPos + 10, true, Graphics::Colors::LightBlue, Graphics::Colors::CobaltBlue);

						window.GetMainPanel().AddComponent(toggleButton1);
						window.GetMainPanel().AddComponent(toggleButton2);
						window.GetMainPanel().AddComponent(toggleButton3);
						window.GetMainPanel().AddComponent(toggleButton4);
					
						CheckBox& selected0 = (CheckBox&)*(window.GetMainPanel().GetComponents()[0]);
						CheckBox& selected1 = (CheckBox&)*(window.GetMainPanel().GetComponents()[1]);
						CheckBox& selected2 = (CheckBox&)*(window.GetMainPanel().GetComponents()[2]);
						CheckBox& selected3 = (CheckBox&)*(window.GetMainPanel().GetComponents()[3]);
						
						selected0.Toggle();
						selected1.Toggle();
						selected2.Toggle();
						selected3.Toggle();

						ToggleButton& selected4 = (ToggleButton&)*(window.GetMainPanel().GetComponents()[4]);
						ToggleButton& selected5 = (ToggleButton&)*(window.GetMainPanel().GetComponents()[5]);
						ToggleButton& selected6 = (ToggleButton&)*(window.GetMainPanel().GetComponents()[6]);
						ToggleButton& selected7 = (ToggleButton&)*(window.GetMainPanel().GetComponents()[7]);

						selected4.Toggle();
						selected5.Toggle();
						selected6.Toggle();
						selected7.Toggle();
					}
					//

					window.KeyReleased(ConvertKeybordKeyToKey(key));
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_WinHandle, [](GLFWwindow* winHandle, int key, int action, int mods) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			double xPos;
			double yPos;

			glfwGetCursorPos(winHandle, &xPos, &yPos);
			yPos = (double)window.GetHeight() - yPos;

			switch (action)
			{
				case GLFW_PRESS:
				{
					window.MouseKeyPressed(ConvertMouseButtonKeyToKey(key), xPos, yPos);
					break;
				}
				case GLFW_REPEAT:
				{
					window.MouseKeyPressed(ConvertMouseButtonKeyToKey(key), xPos, yPos);
					break;
				}
				case GLFW_RELEASE:
				{
					window.MouseKeyReleased(ConvertMouseButtonKeyToKey(key), xPos, yPos);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(m_WinHandle, [](GLFWwindow* winHandle, double xPos, double yPos) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			yPos = (double)window.GetHeight() - yPos;

			window.MouseHover(xPos, yPos);
		});

		glfwSetScrollCallback(m_WinHandle, [](GLFWwindow* winHandle, double xOffset, double yOffset) {
			Editor::EditorWindow& window = *(Editor::EditorWindow*)glfwGetWindowUserPointer(winHandle);

			window.MouseScrolled(yOffset);
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
			NW_INFO(NW_LOGGER_CORE, "Clossing the window \"{}\"", m_Title);

			glfwDestroyWindow(m_WinHandle);
			m_WinHandle = nullptr;
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