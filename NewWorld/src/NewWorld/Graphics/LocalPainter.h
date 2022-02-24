#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/EditorWindow.h"

namespace NewWorld::Graphics
{
	// This is static class
	class LocalPainter : public Object
	{
		NW_CLASS(NewWorld::Graphics, LocalPainter)

			// Members
	private:
		RawPointer<Editor::EditorWindow> m_Window;

		// Getters
	public:
		RawPointer<Editor::EditorWindow> GetWindow() const { return m_Window; }

		// Actions
	public:


	};
}
