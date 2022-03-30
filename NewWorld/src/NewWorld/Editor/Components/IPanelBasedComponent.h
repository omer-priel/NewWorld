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
		inline float GetWidth() const;
		inline float GetHeight() const;
	};
}