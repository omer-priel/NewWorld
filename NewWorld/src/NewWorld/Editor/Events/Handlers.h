#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Input/Key.h"
#include "NewWorld/Editor/Components/IComponent.h"

namespace NewWorld::Editor::Events
{
	using EventHandler = Function<void, Components::IComponent&>;
	void EmptyEventHandler(Components::IComponent& sender);

	using KeyPressedEventHandler = Function<void, Components::IComponent&, Input::Key>;
	void EmptyKeyPressedEventHandler(Components::IComponent& sender, Input::Key key);

	using KeyReleasedEventHandler = Function<void, Components::IComponent&, Input::Key>;
	void EmptyKeyReleasedEventHandler(Components::IComponent& sender, Input::Key key);

	using MouseKeyPressedEventHandler = Function<void, Components::IComponent&, Input::Key, float, float>;
	void EmptyMouseKeyPressedEventHandler(Components::IComponent& sender, Input::Key key, float xPos, float yPos);

	using MouseKeyReleasedEventHandler = Function<void, Components::IComponent&, Input::Key, float, float>;
	void EmptyMouseKeyReleasedEventHandler(Components::IComponent& sender, Input::Key key, float xPos, float yPos);

	using MouseHoverEventHandler = Function<void, Components::IComponent&, float, float>;
	void EmptyMouseHoverEventHandler(Components::IComponent& sender, float xPos, float yPos);

	using MouseScrolledEventHandler = Function<void, Components::IComponent&, int>;
	void EmptyMouseScrolledEventHandler(Components::IComponent& sender, int y);
}