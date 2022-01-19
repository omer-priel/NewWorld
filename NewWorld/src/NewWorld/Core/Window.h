#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Core/GraphicsAPI/GraphicsAPI.h"

struct GLFWwindow;

namespace NewWorld::Core
{
	class Window : public Object
	{
	NW_CLASS(NewWorld::Core, Window)

		// Static
	public:
		static void Initialize();
		static void Finalize();

		// Members
	private:
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

		inline uint GetWidth() const { return m_Width; };
		
		inline uint GetHeight() const { return m_Height; };

		inline bool IsAlive() const { return m_WinHandle != nullptr; };

		bool IsVisible() const;

		// Actions
	public:
		void Create();

		void ReggisterEvents();

		void Show();

		void Hide();

		void Close();

		void HandleEvents();

		// Events
	public:
		virtual void OnUpdate();
	};
}