#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Components/IPanelBasedComponent.h"

namespace NewWorld::Editor::Components
{
	class IResizableComponent : virtual public IPanelBasedComponent
	{
	NW_CLASS(NewWorld::Editor::Components, IResizableComponent)

		// Setters
	public:
		virtual void SetWidth(float width) = 0;
		virtual void SetHeight(float height) = 0;
	};
}