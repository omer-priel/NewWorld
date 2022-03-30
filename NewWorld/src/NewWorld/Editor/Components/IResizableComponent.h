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
		virtual void SetWidth(float width);
		virtual void SetHeight(float height);
	};
}