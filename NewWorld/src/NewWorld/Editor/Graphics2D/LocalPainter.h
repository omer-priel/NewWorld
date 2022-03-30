#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/EditorWindow.h"

namespace Editor::Components
{
	class ComponentContainer;
}

namespace NewWorld::Editor::Graphics2D
{
	// This is static class
	class LocalPainter : public Object
	{
	NW_CLASS(NewWorld::Editor::Graphics2D, LocalPainter)
			
		// Members
	private:
		static RawPointer<EditorWindow> m_Window;
		static float m_X;
		static float m_Y;

		// Getters
	public:
		static RawPointer<EditorWindow> GetWindow() { return m_Window; }

		static float GetX() { return m_X; }
		static float GetY() { return m_Y; }

		// Actions
	public:
		static void ChangeWindow(RawPointer<EditorWindow> window)
		{
			m_Window = window;
			m_X = 0;
			m_Y = 0;
		}

		static void Enter(Components::IContainerComponent& component)
		{
			m_X += component.GetX();
			m_Y += component.GetY();
		}

		static void Leave(Components::IContainerComponent& component)
		{
			m_X -= component.GetX();
			m_Y -= component.GetY();
		}
	};
}
