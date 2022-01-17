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
	void Window::Init()
	{
		m_WinHandle = glfwCreateWindow((int)m_Width, (int)m_Height, m_Title.GetPointer(), nullptr, nullptr);
		glfwMakeContextCurrent(m_WinHandle);
		glfwSetWindowUserPointer(m_WinHandle, this);
		glfwSwapInterval(1); // Set VSync true

		NW_INFO(NW_LOGGER_CORE, "Window Created \"{}\" ({}, {}) ", m_Title, m_Width, m_Height);
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
	LRESULT Window::WindowCallback(HWND winHandle, uint actionType, WPARAM wParam, LPARAM lParam)
	{
		if (WM_NCCREATE == actionType) // Why?
		{
			SetWindowLongPtr(winHandle, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
		}
		
		switch (actionType)
		{
			case WM_DESTROY:
			{
				NW_INFO(NW_LOGGER_CORE, "Window Closed \"{}\" ", m_Title);
			}
			break;
			case WM_CLOSE:
			{
				NW_INFO(NW_LOGGER_CORE, "Window Clossing \"{}\" ", m_Title);
			}
			break;
		}
		return DefWindowProcW(winHandle, actionType, wParam, lParam);
	}
}