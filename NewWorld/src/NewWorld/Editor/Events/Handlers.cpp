#include "nwpch.h"
#include "Handlers.h"

#include "NewWorld/Editor/Component.h"

namespace NewWorld::Editor::Events
{
	void EmptyEventHandler(Component& sender) { }

	void EmptyKeyPressedEventHandler(Component& sender, Input::Key key) { }

	void EmptyKeyReleasedEventHandler(Component& sender, Input::Key key) { }

	void EmptyMouseHoverEventHandler(Component& sender, uint xPos, uint yPos) { }

	void EmptyMouseScrolledEventHandler(Component& sender) { }
}