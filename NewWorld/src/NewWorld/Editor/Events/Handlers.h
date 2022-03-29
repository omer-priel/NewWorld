#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Input/Key.h"

namespace NewWorld::Editor::Components
{
	class Component;
}

namespace NewWorld::Editor::Events
{
	class Event;

	using EventHandler = Function<void, Components::Component&>;
	void EmptyEventHandler(Components::Component& sender);

	using KeyPressedEventHandler = Function<void, Components::Component&, Input::Key>;
	void EmptyKeyPressedEventHandler(Components::Component& sender, Input::Key key);

	using KeyReleasedEventHandler = Function<void, Components::Component&, Input::Key>;
	void EmptyKeyReleasedEventHandler(Components::Component& sender, Input::Key key);

	using MouseKeyPressedEventHandler = Function<void, Components::Component&, Input::Key, float, float>;
	void EmptyMouseKeyPressedEventHandler(Components::Component& sender, Input::Key key, float xPos, float yPos);

	using MouseKeyReleasedEventHandler = Function<void, Components::Component&, Input::Key, float, float>;
	void EmptyMouseKeyReleasedEventHandler(Components::Component& sender, Input::Key key, float xPos, float yPos);

	using MouseHoverEventHandler = Function<void, Components::Component&, float, float>;
	void EmptyMouseHoverEventHandler(Components::Component& sender, float xPos, float yPos);

	using MouseScrolledEventHandler = Function<void, Components::Component&, int>;
	void EmptyMouseScrolledEventHandler(Components::Component& sender, int y);
}