#pragma once

#include "NewWorld/Minimal.h"

#include "NewWorld/Core/Window.h"

int main(int argc, char** argv);

namespace NewWorld::Editor
{
	class EditorWindow : public Core::Window
	{
	NW_CLASS(NewWorld::Editor, EditorWindow)

		// Members
	public:
		SizeT m_WindowID;

	public:
		EditorWindow(SizeT m_WindowID, const String& title = "New World", uint width = 1280, uint height = 720)
			: Window(title, width, height), m_WindowID(m_WindowID)
		{

		}
	};
}
