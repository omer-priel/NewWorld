#include "nwpch.h"
#include "Window.h"

namespace NewWorld::Core
{
	// Static
	void Window::Initialize()
	{
		// Create Windows Class
		WNDCLASSEXW windowClass;
		ZeroMemory(&windowClass, sizeof(windowClass));

		windowClass.lpszClassName = L"NewWorld_WindowClass";
		windowClass.cbSize = sizeof(windowClass);
		windowClass.hInstance = GetModuleHandleW(NULL);

		// Set Style
		windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		
		// Set Callback
		windowClass.lpfnWndProc = Window::WindowCallbackStatic;

		// Set Cursor Icon
		windowClass.hCursor = LoadCursorW(NULL, IDC_ARROW);

		// Set window Icon
		windowClass.hIcon = static_cast<HICON>(LoadImageW(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));

		if (!RegisterClassExW(&windowClass))
		{
			NW_CRITICAL(NW_LOGGER_GRAPHICS, "Cannot create Window, because failed to register \"window class\"");
		}
	}

	// Callback of windowClass
	LRESULT CALLBACK Window::WindowCallbackStatic(HWND winHandle, UINT actionType, WPARAM wParam, LPARAM lParam)
	{
		return ((Window*)GetWindowLongPtr(winHandle, GWLP_USERDATA))->WindowCallback(winHandle, actionType, wParam, lParam);
	}

	// None-Static
	void Window::Init()
	{
		// Set Title
		RawPointer<wchar_t> titleArr = new wchar_t[m_Title.GetLength() + 1];
		mbstowcs(titleArr, m_Title.GetPointer(), m_Title.GetLength() + 1);
		LPWSTR title = titleArr;

		// Set Window Style
		DWORD basicStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN
			| WS_CAPTION | WS_SYSMENU
			| WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
		//| WS_POPUP;
		
		DWORD extraStyle = WS_EX_APPWINDOW;

		// Set Location
		int x = CW_USEDEFAULT; // Gives the OS to select the postion
		int y = CW_USEDEFAULT; // Gives the OS to select the postion

		// Create the Window
		m_WinHandle = CreateWindowExW(extraStyle, L"NewWorld_WindowClass", title, basicStyle,
			x, y, (int)m_Width, (int)m_Height,
			NULL, NULL, GetModuleHandleW(NULL), this);

		NW_INFO(NW_LOGGER_CORE, "Window Created {} ({}, {}) ", m_Title, m_Width, m_Height);
	}

	void Window::Show()
	{
		ShowWindow(m_WinHandle, SW_SHOWNA);
	}

	// Events
	LRESULT Window::WindowCallback(HWND winHandle, uint actionType, WPARAM wParam, LPARAM lParam)
	{
		if (WM_NCCREATE == actionType) // Why?
		{
			SetWindowLongPtr(winHandle, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
			//return TRUE;
		}
		
		switch (actionType)
		{
			case WM_SIZE:
			{
				NW_INFO(NW_LOGGER_CORE, "WM_SIZE");
			}
			break;
			case WM_CLOSE:
			{
				NW_INFO(NW_LOGGER_CORE, "WM_CLOSE");
			}
			break;
		}
		return DefWindowProcW(winHandle, actionType, wParam, lParam);
	}
}