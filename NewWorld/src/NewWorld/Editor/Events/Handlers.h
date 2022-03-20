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

	using MouseKeyPressedEventHandler = Function<void, Component&, Input::Key, float, float>;
	void EmptyMouseKeyPressedEventHandler(Component& sender, Input::Key key, float xPos, float yPos);

	using MouseKeyReleasedEventHandler = Function<void, Component&, Input::Key, float, float>;
	void EmptyMouseKeyReleasedEventHandler(Component& sender, Input::Key key, float xPos, float yPos);

	using MouseHoverEventHandler = Function<void, Component&, float, float>;
	void EmptyMouseHoverEventHandler(Component& sender, float xPos, float yPos);

	using MouseScrolledEventHandler = Function<void, Component&, int>;
	void EmptyMouseScrolledEventHandler(Component& sender, int y);
}