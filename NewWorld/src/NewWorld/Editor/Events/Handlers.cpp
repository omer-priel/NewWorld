#include "nwpch.h"
#include "Handlers.h"

#include "NewWorld/Editor/Components/Component.h"

namespace NewWorld::Editor::Events
{
	// General
	void EmptyEventHandler(Components::Component& sender) { }

	// Keybord
	void EmptyKeyPressedEventHandler(Components::Component& sender, Input::Key key) { }

	void EmptyKeyReleasedEventHandler(Components::Component& sender, Input::Key key) { }

	// Mouse
	void EmptyMouseKeyPressedEventHandler(Components::Component& sender, Input::Key key, float xPos, float yPos) { }

	void EmptyMouseKeyReleasedEventHandler(Components::Component& sender, Input::Key key, float xPos, float yPos) { }

	void EmptyMouseHoverEventHandler(Components::Component& sender, float xPos, float yPos) { }

	void EmptyMouseScrolledEventHandler(Components::Component& sender, int y) { }
}