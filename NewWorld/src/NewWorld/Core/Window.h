#pragma once

#include "NewWorld/Minimal.h"

struct GLFWwindow;

namespace NewWorld::Core
{
	class Window : public Object
	{
	NW_CLASS(NewWorld::Core, Window)

		// Members
	private:
		bool m_ShouldToClose = false;

		String m_Title;
		uint m_Width;
		uint m_Height;

	private:
		GLFWwindow* m_WinHandle = nullptr;

	public:
		Window(const String& title = "New World", uint width = 1280, uint height = 720)
			: m_Title(title), m_Width(width), m_Height(height)
		{

		}

		// Getters
	public:
		inline const String& GetTitle() const { return m_Title; }

		uint GetWidth() const { return m_Width; }
		
		uint GetHeight() const { return m_Height; }

		inline bool IsAlive() const { return m_WinHandle != nullptr; }

		bool IsVisible() const;

		// Actions
	public:
		virtual void Create();

		void ReggisterEvents();

		void Show();

		void Hide();

		virtual void Close();

		bool CloseIfNeed();

		void HandleEvents();

		// Events
	public:
		virtual void Update();
	};
}