#include "nwpch.h"
#include "Handlers.h"

#include "NewWorld/Editor/Component.h"

namespace NewWorld::Editor::Events
{
	// General
	void EmptyEventHandler(Component& sender) { }

	// Keybord
	void EmptyKeyPressedEventHandler(Component& sender, Input::Key key) { }

	void EmptyKeyReleasedEventHandler(Component& sender, Input::Key key) { }

	// Mouse
	void EmptyMouseKeyPressedEventHandler(Component& sender, Input::Key key, uint xPos, uint yPos) { }

	void EmptyMouseKeyReleasedEventHandler(Component& sender, Input::Key key, uint xPos, uint yPos) { }

	void EmptyMouseHoverEventHandler(Component& sender, uint xPos, uint yPos) { }

	void EmptyMouseScrolledEventHandler(Component& sender, uint y) { }
}