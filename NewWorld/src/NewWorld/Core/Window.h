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
		bool m_Visible;
		bool m_VSync;

	private:
		HWND m_WinHandle = nullptr;

	public:
		Window(const String& title = "New World", uint width = 1280, uint height = 720, bool visible = true, bool vSync = true)
			: m_Title(title), m_Width(width), m_Height(height), m_Visible(visible), m_VSync(vSync)
		{

		}

		// Getters
	public:
		inline const String& GetTitle() const { return m_Title; }

		inline uint GetWidth() const { return m_Width; };
		
		inline uint GetHeight() const { return m_Height; };

		inline bool IsVisible() const { return m_Visible; };

		inline bool IsVSync() const { return m_VSync; };

		// Setters
	public:
		void SetVSync(bool enabled);

		void SetVisible(bool visible);

		// Actions
	public:
		void Init();

		void Show();

		//void AddEventCallback(const EventCallback& callback);

		//void Update()

		// OS Events
	private:
		LRESULT WindowCallback(HWND winHandle, UINT actionType, WPARAM wParam, LPARAM lParam);
	};
}