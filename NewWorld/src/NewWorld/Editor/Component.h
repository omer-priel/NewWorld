#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Events/ClickEvent.h"

namespace NewWorld::Editor
{
	class EditorWindow;

	class Component : public Object
	{
	NW_CLASS(NewWorld::Editor, Component)

		// Static Empty Events
	private:
		static void EmptyClickHandler(const Events::ClickEvent& e) {}

		// Members
	private:
		RawPointer<EditorWindow> m_Window;

	protected:
		uint m_X;
		uint m_Y;
		uint m_Width;
		uint m_Height;

	private:
		Events::ClickHandler m_ClickHandler;

	protected:
		Component(uint x, uint y, uint width, uint height)
			: m_Window(nullptr), m_X(x), m_Y(y), m_Width(width), m_Height(height)
			, m_ClickHandler(EmptyClickHandler)
		{

		}

		//  Virtual functions
	public:
		virtual void Create() { }
		virtual void Destroy() { }

		virtual void Update() {}

		// Getters
	public:
		RawPointer<EditorWindow> GetWindow() const
		{
			return m_Window;
		}

		inline uint GetX() const { return m_X; }
		inline uint GetY() const { return m_Y; }

		inline uint GetWidth() const { return m_Width; }
		inline uint GetHeight() const { return m_Height; }

		inline bool IsIn(uint x, uint y) const
		{
			return (m_X <= x && x <= m_X + m_Width) && (m_Y <= y && y <= m_Y + m_Height);
		}

		// Setters
	public:
		void SetWindow(RawPointer<EditorWindow> window) {m_Window = window; }

		void SetClickHandler(Events::ClickHandler handler) { m_ClickHandler = handler; }

		// Events
	public:
		virtual void Click(const Events::ClickEvent& e);
	};
}