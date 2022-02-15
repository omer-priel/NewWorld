#pragma once

#include "NewWorld/Minimal.h"

namespace NewWorld::Editor
{
	class Component;
}

namespace NewWorld::Editor::Events
{
	class Event;

	using EmptyHandler = Function<void, Component&>;

	class Event : public Object
	{
	NW_CLASS(NewWorld::Editor::Events, Event)

		// Static
	public:
		static void EmptyHandler(Component& sender) { }

		// Members
	public:

	};
}