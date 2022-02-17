#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Input/Key.h"

namespace NewWorld::Editor
{
	class Component;
}

namespace NewWorld::Editor::Events
{
	class Event;

	using EventHandler = Function<void, Component&>;
	void EmptyEventHandler(Component& sender);

	using KeyPressedEventHandler = Function<void, Component&, Input::Key>;
	void EmptyKeyPressedEventHandler(Component& sender, Input::Key key);

	using KeyReleasedEventHandler = Function<void, Component&, Input::Key>;
	void EmptyKeyReleasedEventHandler(Component& sender, Input::Key key);

	using MouseKeyPressedEventHandler = Function<void, Component&, Input::Key, uint, uint>;
	void EmptyMouseKeyPressedEventHandler(Component& sender, Input::Key key, uint xPos, uint yPos);

	using MouseKeyReleasedEventHandler = Function<void, Component&, Input::Key, uint, uint>;
	void EmptyMouseKeyReleasedEventHandler(Component& sender, Input::Key key, uint xPos, uint yPos);

	using MouseHoverEventHandler = Function<void, Component&, uint, uint>;
	void EmptyMouseHoverEventHandler(Component& sender, uint xPos, uint yPos);

	using MouseScrolledEventHandler = Function<void, Component&>;
	void EmptyMouseScrolledEventHandler(Component& sender);
}