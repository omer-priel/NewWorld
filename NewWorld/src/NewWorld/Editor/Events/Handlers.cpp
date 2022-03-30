#include "nwpch.h"
#include "Handlers.h"

namespace NewWorld::Editor::Events
{
	// General
	void EmptyEventHandler(Components::IComponent& sender) { }

	// Keybord
	void EmptyKeyPressedEventHandler(Components::IComponent& sender, Input::Key key) { }

	void EmptyKeyReleasedEventHandler(Components::IComponent& sender, Input::Key key) { }

	// Mouse
	void EmptyMouseKeyPressedEventHandler(Components::IComponent& sender, Input::Key key, float xPos, float yPos) { }

	void EmptyMouseKeyReleasedEventHandler(Components::IComponent& sender, Input::Key key, float xPos, float yPos) { }

	void EmptyMouseHoverEventHandler(Components::IComponent& sender, float xPos, float yPos) { }

	void EmptyMouseScrolledEventHandler(Components::IComponent& sender, int y) { }
}