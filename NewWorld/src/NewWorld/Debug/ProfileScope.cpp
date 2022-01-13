#include "nwpch.h"
#include "ProfileScope.h"

namespace NewWorld::Debug
{
	ProfileScope::ProfileScope(const String& name)
		: m_Name(name), m_Start(Time::Now().GetTicks())
	{

	}

	ProfileScope::~ProfileScope()
	{
		Profiler::AddScope(m_Name, m_Start, Time::Now().GetTicks());
	}
}