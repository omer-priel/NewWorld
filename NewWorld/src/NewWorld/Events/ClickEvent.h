#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Events/Event.h"

#include "NewWorld/Input/Key.h"

namespace NewWorld::Events
{
	class ClickEvent;

	using ClickHandler = Function<void, const ClickEvent&>;

	class ClickEvent : public Event
	{
	NW_CLASS(NewWorld::Events, ClickEvent)

		// Members
	private:
		Input::Key m_Key;
		uint m_X;
		uint m_Y;

	public:
		ClickEvent(Input::Key key, uint x, uint y)
			: m_Key(key), m_X(x), m_Y(y)
		{

		}

		// Getters
	public:
		inline Input::Key GetKey() const { return m_Key; }

		inline uint GetX() const { return m_X; }
		inline uint GetY() const { return m_Y; }
	};
}