#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Components/IComponent.h"

namespace NewWorld::Editor::Components
{
	class IPanelBasedComponent : virtual public IComponent
	{
	NW_CLASS(NewWorld::Editor::Components, IPanelBasedComponent)

		// Getters
	public:
		virtual inline float GetWidth() const = 0;
		virtual inline float GetHeight() const = 0;

		virtual bool IsIn(float x, float y) const override
		{
			return (GetX() <= x && x <= GetX() + GetWidth()) && (GetY() <= y && y <= GetY() + GetHeight());
		}
	};
}