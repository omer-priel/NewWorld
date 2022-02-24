#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/EditorWindow.h"

namespace Editor
{
	class ComponentContainer;
}

namespace NewWorld::Graphics
{
	// This is static class
	class LocalPainter : public Object
	{
	NW_CLASS(NewWorld::Graphics, LocalPainter)
			
		// Members
	private:
		static RawPointer<Editor::EditorWindow> m_Window;
		static int m_X;
		static int m_Y;

		// Getters
	public:
		static RawPointer<Editor::EditorWindow> GetWindow() { return m_Window; }

		static int GetX() { return m_X; }
		static int GetY() { return m_Y; }

		// Actions
	public:
		static void ChangeWindow(RawPointer<Editor::EditorWindow> window)
		{
			m_Window = window;
			m_X = 0;
			m_Y = 0;
		}

		static void Enter(Editor::ComponentContainer& component)
		{
			m_X += component.GetX();
			m_Y += component.GetY();
		}

		static void Leave(Editor::ComponentContainer& component)
		{
			m_X -= component.GetX();
			m_Y -= component.GetY();
		}
	};
}
