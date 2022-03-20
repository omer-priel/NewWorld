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
	void EmptyMouseKeyPressedEventHandler(Component& sender, Input::Key key, float xPos, float yPos) { }

	void EmptyMouseKeyReleasedEventHandler(Component& sender, Input::Key key, float xPos, float yPos) { }

	void EmptyMouseHoverEventHandler(Component& sender, float xPos, float yPos) { }

	void EmptyMouseScrolledEventHandler(Component& sender, int y) { }
}