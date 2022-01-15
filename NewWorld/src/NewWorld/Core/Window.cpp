#include "nwpch.h"
#include "Window.h"

namespace NewWorld::Core
{
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProcW(hwnd, uMsg, wParam, lParam);
	}

	void Window::Init()
	{
		LPCWSTR lpWindowName = (LPCWSTR)m_Title.GetPointer();
		
		// Create Windows Class
		WNDCLASSEXW windowClass;
		ZeroMemory(&windowClass, sizeof(windowClass));
		
		windowClass.lpszClassName = L"NewWorld_WindowClass";
		windowClass.cbSize = sizeof(windowClass);
		windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		windowClass.lpfnWndProc = WindowProc;
		windowClass.hInstance = GetModuleHandleW(NULL);
		windowClass.hCursor = LoadCursorW(NULL, IDC_ARROW);

		//windowClass.hIcon = LoadImageW(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);

		if (!RegisterClassExW(&windowClass))
		{
			//NW_CRITICAL(NW_LOGGER_GRA, "Win32: Failed to register window class");
		}

		// Set Cursor Icon
		LoadIcon(NULL, IDC_ARROW);

		// Set Window Style
		// https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles
		// https://docs.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles

		DWORD dwStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN
			| WS_CAPTION | WS_SYSMENU
			| WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
		//| WS_POPUP;
		
		DWORD dwExStyle = WS_EX_APPWINDOW;

		// Set Location
		int x = CW_USEDEFAULT; // Gives the OS to select the postion
		int y = CW_USEDEFAULT; // Gives the OS to select the postion
		
		// Set extra window settings
		HWND      hWndParent = NULL;
		HMENU     hMenu = NULL;
		HINSTANCE hInstance = GetModuleHandleW(NULL);
		LPVOID    lpParam = NULL;

		// Create the Window
		m_WinHandle = CreateWindowExW(dwExStyle, windowClass.lpszClassName, lpWindowName, dwStyle,
			x, y, (int)m_Width, (int)m_Height,
			hWndParent, hMenu, hInstance, lpParam);

		NW_INFO(NW_LOGGER_CORE, "Window Created {} ({}, {}) ", m_Title, m_Width, m_Height);
	}

	void Window::Show()
	{
		// TODO: Show
		ShowWindow(m_WinHandle, SW_SHOWNA);
	}
}