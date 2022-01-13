#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Debug/Profiler.h"

namespace NewWorld::Debug
{
	class ProfileScope : public Object
	{
	NW_CLASS(NewWorld::Debug, ProfileScope)

		// Members
	public:
		String m_Name;
		Long m_Start;

	public:
		ProfileScope(const String& name);

		~ProfileScope();
	};
}
