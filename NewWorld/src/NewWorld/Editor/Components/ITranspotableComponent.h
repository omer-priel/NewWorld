#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Components/IComponent.h"

namespace NewWorld::Editor::Components
{
	class ITranspotableComponent : virtual public IComponent
	{
	NW_CLASS(NewWorld::Editor::Components, ITranspotableComponent)

		// Setters
	public:
		virtual void SetX(float x) = 0;
		virtual void SetY(float y) = 0;
	};
}