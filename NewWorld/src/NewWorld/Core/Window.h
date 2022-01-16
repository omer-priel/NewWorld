#pragma once

#include "NewWorld/Minimal.h"

namespace NewWorld::Core
{
	class Window : public Object
	{
	NW_CLASS(NewWorld::Core, Window)

		// Static
	public:
		static void Initialize();

	private:
		static LRESULT CALLBACK WindowCallbackStatic(HWND winHandle, UINT actionType, WPARAM wParam, LPARAM lParam);

		// Members
	private:
		String m_Title;
		uint m_Width;
		uint m_Height;

	private:
		HWND m_WinHandle = nullptr;

	public:
		Window(const String& title = "New World", uint width = 1280, uint height = 720)
			: m_Title(title), m_Width(width), m_Height(height)
		{

		}

		// Getters
	public:
		inline const String& GetTitle() const { return m_Title; }

		inline uint GetWidth() const { return m_Width; };
		
		inline uint GetHeight() const { return m_Height; };

		inline bool IsAlive() const { return m_WinHandle != nullptr; };

		inline bool IsVisible() const { return IsWindowVisible(m_WinHandle); };

		// Actions
	public:
		void Init();

		void Show();

		void Hide();

		void Close();

		void HandleEvents();

	private:
		LRESULT WindowCallback(HWND winHandle, UINT actionType, WPARAM wParam, LPARAM lParam);
	};
}