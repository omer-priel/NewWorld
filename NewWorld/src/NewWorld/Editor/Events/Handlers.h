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
}