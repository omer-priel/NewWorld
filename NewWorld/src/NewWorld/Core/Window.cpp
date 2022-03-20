#include "nwpch.h"
#include "Window.h"

#include "NewWorld/Input/Key.h"
#include "NewWorld/Editor/EditorWindow.h"

#include "NewWorld/Editor/UI/Button.h"
#include "NewWorld/Editor/UI/BordedLabel.h"
#include "NewWorld/Editor/UI/CheckBox.h"
#include "NewWorld/Editor/UI/ToggleButton.h"
#include "NewWorld/Editor/UI/RadioButton.h"
#include "NewWorld/Editor/UI/RadioButtonGroup.h"

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

	static void test1(Editor::EditorWindow& window, uint xPos, uint yPos)
	{
		using namespace NewWorld::Graphics;
		using namespace NewWorld::Editor;
		using namespace NewWorld::Editor::UI;
		// CheckBox
		SharedPointer<CheckBox> checkBox1(xPos - 24, yPos - 24);
		SharedPointer<CheckBox> checkBox2(xPos + 10, yPos - 24, true);
		SharedPointer<CheckBox> checkBox3(xPos - 24, yPos + 10, false, Colors::LightBlue, Colors::CobaltBlue);
		SharedPointer<CheckBox> checkBox4(xPos + 10, yPos + 10, true, Colors::LightBlue, Colors::CobaltBlue);

		window.GetMainPanel().AddComponent(checkBox1);
		window.GetMainPanel().AddComponent(checkBox2);
		window.GetMainPanel().AddComponent(checkBox3);
		window.GetMainPanel().AddComponent(checkBox4);

		// ToggleButton
		SharedPointer<ToggleButton> toggleButton1(xPos + 100 - 24, yPos - 24);
		SharedPointer<ToggleButton> toggleButton2(xPos + 100 + 10, yPos - 24, true);
		SharedPointer<ToggleButton> toggleButton3(xPos + 100 - 24, yPos + 10, false, Colors::LightBlue, Colors::CobaltBlue);
		SharedPointer<ToggleButton> toggleButton4(xPos + 100 + 10, yPos + 10, true, Colors::LightBlue, Colors::CobaltBlue);

		window.GetMainPanel().AddComponent(toggleButton1);
		window.GetMainPanel().AddComponent(toggleButton2);
		window.GetMainPanel().AddComponent(toggleButton3);
		window.GetMainPanel().AddComponent(toggleButton4);

		// Button
		SharedPointer<Button> button1(xPos + 100 - 24, yPos + 150 + 100, 100, 30, "Test 1", Colors::CobaltBlue);
		SharedPointer<Button> button2(xPos + 100 - 24, yPos + 150 + 50, 100, 30, "Test 2");
		SharedPointer<Button> button3(xPos + 100 - 24, yPos + 150 + 0, 100, 30, "Test 3");

		button1->SetClickHandler([](Component& sender) {
			Button& button = (Button&)sender;

			static bool flag = false;

			flag = !flag;

			if (!flag)
			{
				button.SetBackgroundColor(Colors::CobaltBlue);
			}
			else
			{
				button.SetBackgroundColor(Colors::LightBlue);
			}

			});

		button2->SetClickHandler([](Component& sender) {
			Button& button = (Button&)sender;

			static int clicks = 0;

			clicks++;

			button.SetText(String::ConverToString(clicks));
			});

		button3->SetClickHandler([](Component& sender) {
			Button& button = (Button&)sender;

			static int clicks = 0;

			clicks++;

			button.SetText(String::Format("{} Clicks", clicks));
			});

		window.GetMainPanel().AddComponent(button1);
		window.GetMainPanel().AddComponent(button2);
		window.GetMainPanel().AddComponent(button3);

		// RadioButton
		SharedPointer<RadioButton> radioButton01(xPos + 200, yPos - 7);

		window.GetMainPanel().AddComponent(radioButton01);

		SharedPointer<RadioButtonGroup> radioButtonGroup1;

		window.GetMainPanel().AddComponent(radioButtonGroup1);

		SharedPointer<RadioButton> radioButton11(xPos + 250, yPos - 30);
		SharedPointer<RadioButton> radioButton12(xPos + 250, yPos - 7);
		SharedPointer<RadioButton> radioButton13(xPos + 250, yPos + 14);

		radioButtonGroup1->AddRadioButton(radioButton11);
		radioButtonGroup1->AddRadioButton(radioButton12);
		radioButtonGroup1->AddRadioButton(radioButton13);

		window.GetMainPanel().AddComponent(radioButton11);
		window.GetMainPanel().AddComponent(radioButton12);
		window.GetMainPanel().AddComponent(radioButton13);

		SharedPointer<RadioButtonGroup> radioButtonGroup2;

		window.GetMainPanel().AddComponent(radioButtonGroup2);

		SharedPointer<RadioButton> radioButton21(xPos + 300, yPos - 30,
			Colors::Transparency, Colors::EditorDarkValue,
			Colors::LimeGreen);
		SharedPointer<RadioButton> radioButton22(xPos + 300, yPos - 7,
			Colors::Transparency, Colors::EditorDarkValue,
			Colors::Orange);
		SharedPointer<RadioButton> radioButton23(xPos + 300, yPos + 14,
			Colors::Transparency, Colors::EditorDarkValue,
			Colors::Red);

		radioButtonGroup2->AddRadioButton(radioButton21);
		radioButtonGroup2->AddRadioButton(radioButton22);
		radioButtonGroup2->AddRadioButton(radioButton23);

		radioButton23->Toggle();

		window.GetMainPanel().AddComponent(radioButton21);
		window.GetMainPanel().AddComponent(radioButton22);
		window.GetMainPanel().AddComponent(radioButton23);

		// RadioButton all the Colors
		SharedPointer<RadioButtonGroup> radioButtonGroupAllColors;

		window.GetMainPanel().AddComponent(radioButtonGroupAllColors);

		class ColorWithName
		{
		public:
			String Name;
			Color Color;

			ColorWithName(const String& name, const Graphics::Color& color)
				: Name(name), Color(color) {}
		};

		Array<ColorWithName, 32> colors = {
			ColorWithName("Black", Colors::Black),
			ColorWithName("White", Colors::White),
			ColorWithName("Red", Colors::Red),
			ColorWithName("Green", Colors::Green),
			ColorWithName("Blue", Colors::Blue),
			ColorWithName("Cyan", Colors::Cyan),
			ColorWithName("Magenta", Colors::Magenta),
			ColorWithName("Yellow", Colors::Yellow),
			ColorWithName("Gray", Colors::Gray),
			ColorWithName("Orange", Colors::Orange),
			ColorWithName("Pink", Colors::Pink),
			ColorWithName("Gold", Colors::Gold),
			ColorWithName("DarkRed", Colors::DarkRed),
			ColorWithName("Ruby", Colors::Ruby),
			ColorWithName("NeonRed", Colors::NeonRed),
			ColorWithName("RoseRed", Colors::RoseRed),
			ColorWithName("Coral", Colors::Coral),
			ColorWithName("DarkGreen", Colors::DarkGreen),
			ColorWithName("ForestGreen", Colors::ForestGreen),
			ColorWithName("LimeGreen", Colors::LimeGreen),
			ColorWithName("KellyGreen", Colors::KellyGreen),
			ColorWithName("LightGreen", Colors::LightGreen),
			ColorWithName("NavyBlue", Colors::NavyBlue),
			ColorWithName("CobaltBlue", Colors::CobaltBlue),
			ColorWithName("RoyalBlue", Colors::RoyalBlue),
			ColorWithName("LightBlue", Colors::LightBlue),
			ColorWithName("Turquoise", Colors::Turquoise),
			ColorWithName("DarkGray", Colors::DarkGray),
			ColorWithName("LightGray", Colors::LightGray),
			ColorWithName("Charcoal", Colors::Charcoal),
			ColorWithName("SlateGray", Colors::SlateGray),
			ColorWithName("Silver", Colors::Silver)
		};

		for (size_t i = 0; i < colors.size(); i++)
		{
			SharedPointer<RadioButton> radioButtonColor(
				xPos + 350 + (i / 10) * 200, yPos + 200 + 5 - (i % 10) * 40,
				Colors::Transparency, Colors::EditorDarkValue,
				colors[i].Color);

			SharedPointer<BordedLabel> labelColor(
				xPos + 350 + (i / 10) * 200 + 25, yPos + 200 - (i % 10) * 40,
				colors[i].Name, 150, (TextAlign)((i / 10) % 3),
				Colors::Transparency, colors[i].Color,
				Colors::Black);

			radioButtonGroupAllColors->AddRadioButton(radioButtonColor);

			window.GetMainPanel().AddComponent(radioButtonColor);
			window.GetMainPanel().AddComponent(labelColor);
		}

		// Changes
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

	static void test2(Editor::EditorWindow& window, uint xPos, uint yPos)
	{
		using namespace NewWorld::Graphics;
		using namespace NewWorld::Editor;
		using namespace NewWorld::Editor::UI;


	}

	static void test(Editor::EditorWindow& window, uint xPos, uint yPos)
	{
		test1(window, xPos, yPos);
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

						// Create new UI Components
						test(window, xPos, yPos);
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