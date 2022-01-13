#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Debug/Profiler.h"

namespace NewWorld::Debug
{
	class ProfileBlock : public Object
	{
	NW_CLASS(NewWorld::Debug, ProfileBlock)

		// Members
	public:
		String m_Name;
		Long m_Start;

	public:
		ProfileBlock(const String& name)
			: m_Name(name), m_Start(Time::Now().GetTicks())
		{

		}

		~ProfileBlock()
		{
			Profiler::AddBlock(m_Name, m_Start, Time::Now().GetTicks());
		}
	};
}
