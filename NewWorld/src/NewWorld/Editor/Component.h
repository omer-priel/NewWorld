#pragma once

#include "NewWorld/Minimal.h"

namespace NewWorld::Editor
{
	class Component abstract : public Object
	{
	NW_CLASS(NewWorld::Editor, Component)

		// Pure virtual functions
	public:
		virtual void Create() = 0;
		virtual void Destroy() = 0;
	};
}